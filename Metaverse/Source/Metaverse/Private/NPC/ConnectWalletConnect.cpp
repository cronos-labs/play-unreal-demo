// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/ConnectWalletConnect.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"

// Called when the game starts or when spawned
void AConnectWalletConnect::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &AConnectWalletConnect::OnConnectWalletConnectBeginOverlap);
}

void AConnectWalletConnect::OnConnectWalletConnectBeginOverlap(
    UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult &SweepResult) {
    AMetaverseCharacter *MetaverseCharacter =
        Cast<AMetaverseCharacter>(OtherActor);
    if (MetaverseCharacter->GetAccount().IsEmpty()) {
        MetaverseCharacter->SetAccount(
            FText::FromString(FString::Printf(TEXT("Plase scan QR Code"))));
    } else {
        MetaverseCharacter->SetAccount(MetaverseCharacter->GetAccount());
    }

    UWalletConnectTriggerComponent *WalletConnectTriggerComponent =
        GetWalletConnectTriggerComponent();

    WalletConnectTriggerComponent->Connect();

    WalletConnectTriggerComponent->OnShowQR.BindDynamic(this, &Super::ShowQR);
}
