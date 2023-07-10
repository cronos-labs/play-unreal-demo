// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC/Help.h"
#include "DynamicContractObject.h"
#include "CallDynamicContract.generated.h"

/**
 *
 */
UCLASS()
class METAVERSE_API ACallDynamicContract : public AHelp {
    GENERATED_BODY()

  protected:
    void Setup();

  public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Contract")
    UDynamicContractObject *UserDynamicContractObject;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnCallDynamicContractBeginOverlap(
        UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult &SweepResult);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Contract")
    FString UserContractAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Contract")
    FString UserContractAbiJson;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Contract")
    FString UserFunctionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Contract")
    FString UserFunctionArgs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Contract")
    FCallDynamicContractDelegate CallDynamicContractCallback;

    UFUNCTION()
    void OnCallDynamicContract(FString JsonResult, FString Result);
};
