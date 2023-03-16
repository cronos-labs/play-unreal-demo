// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/CallDynamicContract.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"

// Called when the game starts or when spawned
void ACallDynamicContract::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &ACallDynamicContract::OnCallDynamicContractBeginOverlap);

    // connect member function to callback variable
    CallDynamicContractCallback.BindDynamic(
        this, &ACallDynamicContract::OnCallDynamicContract);
}

void ACallDynamicContract::OnCallDynamicContractBeginOverlap(
    UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult &SweepResult) {

    AMetaverseCharacter *MetaverseCharacter =
        Cast<AMetaverseCharacter>(OtherActor);
    if (MetaverseCharacter != nullptr) {
        if (UserDynamicContractObject == nullptr) {
            bool success = false;
            FString output_message = "";
            UserDynamicContractObject =
                MetaverseCharacter->CreateDynamicContract(
                    UserContractAddress, UserContractAbiJson, success,
                    output_message);

            if (GEngine) {
                FString ouput = FString::Printf(
                    TEXT("CreateDynamicContract success: %s, output_message: "
                         "%s"),
                    success ? TEXT("true") : TEXT("false"), *output_message);
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, ouput);
            }
        }

        if (UserDynamicContractObject != nullptr) {
            UserDynamicContractObject->CallDynamicContract(
                UserFunctionName, UserFunctionArgs,
                CallDynamicContractCallback);
        }
    }
}

void ACallDynamicContract::OnCallDynamicContract(FString JsonResult,
                                                 FString Result) {
    if (GEngine) {
        FString ouput = FString::Printf(
            TEXT("OnCallDynamicContract JsonResult: %s, Result: %s"),
            *JsonResult, *Result);
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, ouput);
    }
}