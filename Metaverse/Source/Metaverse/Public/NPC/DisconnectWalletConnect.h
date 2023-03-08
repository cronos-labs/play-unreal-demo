// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC/Help.h"
#include "DisconnectWalletConnect.generated.h"

UCLASS()
class METAVERSE_API ADisconnectWalletConnect : public AHelp
{
	GENERATED_BODY()

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnDisconnectWalletConnectBeginOverlap(
        UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult &SweepResult);
};
