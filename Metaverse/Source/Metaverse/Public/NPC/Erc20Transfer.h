// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC/Help.h"
#include "Erc20Transfer.generated.h"

struct FWalletSendTXEip155Result;
class AMetaverseCharacter;

/**
 *
 */
UCLASS()
class METAVERSE_API AErc20Transfer : public AHelp {
	GENERATED_BODY()

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnErc20TransferBeginOverlap(
		UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);

  private:
	UFUNCTION()
        void OnWalletconnectErc20TranferFinished(FWalletSendTXEip155Result TxResult);
  AMetaverseCharacter *MetaverseCharacter;
};
