// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MetaverseCharacter.generated.h"

class UMetaverseOverlay;
class UAttributeComponent;
class UDefiWalletCoreComponent;

UCLASS(config = Game)
class AMetaverseCharacter : public ACharacter {
    GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent *CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    class UCameraComponent *FollowCamera;

    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext *DefaultMappingContext;

    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    class UInputAction *JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    class UInputAction *MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    class UInputAction *LookAction;

  public:
    AMetaverseCharacter();

  protected:
    /** Called for movement input */
    void Move(const FInputActionValue &Value);

    /** Called for looking input */
    void Look(const FInputActionValue &Value);

  protected:
    // APawn interface
    virtual void SetupPlayerInputComponent(
        class UInputComponent *PlayerInputComponent) override;

    // To add mapping context
    virtual void BeginPlay();

  private:
    void InitializeMetaverseOverlay();

    UPROPERTY()
    UMetaverseOverlay *MetaverseOverlay;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
              meta = (AllowPrivateAccess = "true"))
    UAttributeComponent *AttributeComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
              meta = (AllowPrivateAccess = "true"))
    UDefiWalletCoreComponent *DefiWalletCoreComponent;

  public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent *GetCameraBoom() const {
        return CameraBoom;
    }
    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent *GetFollowCamera() const {
        return FollowCamera;
    }
    FText GetAccount();
    void SetAccount(FText account);
    void AddCoin(float value);
    void ShowQR(UTexture2D *QRTexture);
    void HideQR();
    void SetBalance(FText account);

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "CreateDynamicContract",
                      Keywords = "Contract"),
              Category = "MetaverseGame")
    UDynamicContractObject *CreateDynamicContract(FString contractaddress,
                                                  FString abijson,
                                                  bool &success,
                                                  FString &output_message);
};
