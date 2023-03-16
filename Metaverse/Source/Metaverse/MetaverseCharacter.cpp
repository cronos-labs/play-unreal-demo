// Copyright 2022, Cronos Labs. All Rights Reserved

#include "MetaverseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUD/MetaverseOverlay.h"
#include "HUD/MetaverseHUD.h"
#include "Components/AttributeComponent.h"
#include "Components/DefiWalletCoreComponent.h"
#include "DefiWalletCoreActor.h"
#include "Logging/LogVerbosity.h"
#include "DynamicContractObject.h"

// AMetaverseCharacter
AMetaverseCharacter::AMetaverseCharacter() {
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates. Let that just affect the
    // camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement =
        true; // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate =
        FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be
    // tweaked in the Character Blueprint instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // Create a camera boom (pulls in towards the player if there is a
    // collision)
    CameraBoom =
        CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength =
        400.0f; // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation =
        true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera =
        CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(
        CameraBoom,
        USpringArmComponent::SocketName); // Attach the camera to the end of the
                                          // boom and let the boom adjust to
                                          // match the controller orientation
    FollowCamera->bUsePawnControlRotation =
        false; // Camera does not rotate relative to arm

    AttributeComponent =
        CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));

    DefiWalletCoreComponent = CreateDefaultSubobject<UDefiWalletCoreComponent>(
        TEXT("Defi Wallet Core"));

    // Note: The skeletal mesh and anim blueprint references on the Mesh
    // component (inherited from Character) are set in the derived blueprint
    // asset named ThirdPersonCharacter (to avoid direct content references in
    // C++)
}

void AMetaverseCharacter::BeginPlay() {
    // Call the base class
    Super::BeginPlay();

    // Add Input Mapping Context
    if (APlayerController *PlayerController =
            Cast<APlayerController>(Controller)) {
        if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                    PlayerController->GetLocalPlayer())) {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
    InitializeMetaverseOverlay();
    DefiWalletCoreComponent->Setup();
}

// Input
void AMetaverseCharacter::SetupPlayerInputComponent(
    class UInputComponent *PlayerInputComponent) {
    // Set up action bindings
    if (UEnhancedInputComponent *EnhancedInputComponent =
            CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered,
                                           this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed,
                                           this, &ACharacter::StopJumping);

        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
                                           this, &AMetaverseCharacter::Move);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
                                           this, &AMetaverseCharacter::Look);
    }
}

void AMetaverseCharacter::Move(const FInputActionValue &Value) {
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr) {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector ForwardDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // get right vector
        const FVector RightDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // add movement
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AMetaverseCharacter::Look(const FInputActionValue &Value) {
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr) {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AMetaverseCharacter::InitializeMetaverseOverlay() {
    APlayerController *PlayerController =
        Cast<APlayerController>(GetController());
    AMetaverseHUD *MetaverseHUD =
        Cast<AMetaverseHUD>(PlayerController->GetHUD());
    // if MetaverseHUD is valid
    if (MetaverseHUD) {
        MetaverseOverlay = MetaverseHUD->GetMetaverseOverlay();
        MetaverseOverlay->SetBalance(0);
        MetaverseOverlay->SetCoin(0);
        MetaverseOverlay->SetAccount(FText::FromString(FString::Printf(
            TEXT("Please connect a WalletConnect-compatible wallet"))));
    }
}

void AMetaverseCharacter::AddCoin(float value) {
    AttributeComponent->AddCoin(value);                       // update
    MetaverseOverlay->SetCoin(AttributeComponent->GetCoin()); // display
}

FText AMetaverseCharacter::GetAccount() {
    return AttributeComponent->GetAccount();
}

void AMetaverseCharacter::SetAccount(FText account) {
    AttributeComponent->SetAccount(account);                        // update
    MetaverseOverlay->SetAccount(AttributeComponent->GetAccount()); // display
}

void AMetaverseCharacter::SetInitialBalance(FText account) {
    ADefiWalletCoreActor *DefiWalletCore =
        DefiWalletCoreComponent->GetDefiWalletCore();
    if (DefiWalletCore) {
        UE_LOG(LogTemp, Log, TEXT("Getting Balance from: %s..."),
               *account.ToString());
        FString balance;
        bool success;
        FString output_message;
        DefiWalletCore->GetEthBalance(account.ToString(), balance, success,
                                      output_message);
        UE_LOG(LogTemp, Log, TEXT("Balance: %f"), FCString::Atof(*balance));
        if (success) {
            AttributeComponent->SetBalance(FCString::Atof(*balance) /
                                           1000000000000000000); // update
            MetaverseOverlay->SetBalance(
                AttributeComponent->GetBalance()); // display
        } else {
            UE_LOG(LogTemp, Error, TEXT("Can not get CRO balance, Error: %s"),
                   *output_message);
        }
    } else {
        UE_LOG(LogTemp, Error, TEXT("Can not find Defi Wallet Core"));
    }
}

void AMetaverseCharacter::ShowQR(UTexture2D *QRTexture) {
    APlayerController *PlayerController =
        Cast<APlayerController>(GetController());
    AMetaverseHUD *MetaverseHUD =
        Cast<AMetaverseHUD>(PlayerController->GetHUD());
    MetaverseHUD->ShowQR(QRTexture);
}

void AMetaverseCharacter::HideQR() {
    APlayerController *PlayerController =
        Cast<APlayerController>(GetController());
    AMetaverseHUD *MetaverseHUD =
        Cast<AMetaverseHUD>(PlayerController->GetHUD());
    MetaverseHUD->HideQR();
}

UDynamicContractObject *
AMetaverseCharacter::CreateDynamicContract(FString contractaddress,
                                           FString abijson, bool &success,
                                           FString &output_message) {
    ADefiWalletCoreActor *DefiWalletCore =
        DefiWalletCoreComponent->GetDefiWalletCore();
    return DefiWalletCore->CreateDynamicContract(contractaddress, abijson,
                                                 success, output_message);
}