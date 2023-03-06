// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Help.generated.h"

class UWalletConnectTriggerComponent;
class UText3DComponent;
class UMetaverseOverlay;

UCLASS()
class METAVERSE_API AHelp : public AActor {
    GENERATED_BODY()
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
              meta = (AllowPrivateAccess = "true"))
    UWalletConnectTriggerComponent *WalletConnectTrigger;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
              meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent *BaseMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
              meta = (AllowPrivateAccess = "true"))
    UText3DComponent *Text3D;

public:
    // Sets default values for this actor's properties
    AHelp();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    FORCEINLINE UWalletConnectTriggerComponent *
    GetWalletConnectTriggerComponent(){return WalletConnectTrigger;}
	UFUNCTION()
    void ShowQR(UTexture2D *Texture);
    UFUNCTION()
    void HideQR(FString Address, int64 ChainID);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

};
