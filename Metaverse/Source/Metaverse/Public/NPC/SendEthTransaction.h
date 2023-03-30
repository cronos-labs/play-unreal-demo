// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC/Help.h"
#include "SendEthTransaction.generated.h"

struct FWalletSendTXEip155Result;
class AMetaverseCharacter;

/**
 *
 */
UCLASS()
class METAVERSE_API ASendEthTransaction : public AHelp {
    GENERATED_BODY()

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSendEthTransactionBeginOverlap(
        UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult &SweepResult);

  private:
    UFUNCTION()
    void OnWalletconnectSendEip155TransactionFinished(
        FWalletSendTXEip155Result SendResult);
    AMetaverseCharacter *MetaverseCharacter;
};
