// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/Help.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"
#include "Text3DComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHelp::AHelp() {
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    WalletConnectTrigger =
        CreateDefaultSubobject<UWalletConnectTriggerComponent>(
            TEXT("WalletConnect Trigger"));
    RootComponent = WalletConnectTrigger;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(WalletConnectTrigger);

    Text3D =
        CreateDefaultSubobject<UText3DComponent>(TEXT("Operation Message"));
    Text3D->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void AHelp::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AHelp::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AHelp::ShowQR(UTexture2D *Texture) {
    AMetaverseCharacter *MetaverseCharacter = Cast<AMetaverseCharacter>(
        UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    MetaverseCharacter->ShowQR(Texture);

    GetWalletConnectTriggerComponent()->OnHideQRAndUpdateOverlay.BindDynamic(
        this, &AHelp::HideQRAndUpdateOverlay);
}

void AHelp::HideQRAndUpdateOverlay(FString Address, int64 ChainID) {
    AMetaverseCharacter *MetaverseCharacter = Cast<AMetaverseCharacter>(
        UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    MetaverseCharacter->SetAccount(
        FText::FromString(FString::Printf(TEXT("0x%s"), *Address)));

    MetaverseCharacter->SetInitialBalance(
        FText::FromString(FString::Printf(TEXT("0x%s"), *Address)));

    MetaverseCharacter->HideQR();
}

void AHelp::HideQR() {
    AMetaverseCharacter *MetaverseCharacter = Cast<AMetaverseCharacter>(
        UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    MetaverseCharacter->HideQR();
}
