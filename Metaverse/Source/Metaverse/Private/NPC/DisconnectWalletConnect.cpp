// Copyright 2022, Cronos Labs. All Rights Reserved


#include "NPC/DisconnectWalletConnect.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"


// Called when the game starts or when spawned
void ADisconnectWalletConnect::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &ADisconnectWalletConnect::OnDisconnectWalletConnectBeginOverlap);
}

void ADisconnectWalletConnect::OnDisconnectWalletConnectBeginOverlap(
    UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult &SweepResult) {
    AMetaverseCharacter *MetaverseCharacter =
        Cast<AMetaverseCharacter>(OtherActor);
    MetaverseCharacter->SetAccount(
    FText::FromString(FString::Printf(TEXT("Please connect a WalletConnect-compatible wallet"))));

    UWalletConnectTriggerComponent *WalletConnectTriggerComponent = GetWalletConnectTriggerComponent();

    // Hide QR if any
    WalletConnectTriggerComponent->OnHideQR.BindDynamic(
        this, &Super::HideQR);
    WalletConnectTriggerComponent->Disconnect();
}
