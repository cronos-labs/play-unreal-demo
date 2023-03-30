// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/SendEthTransaction.h"

#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"
#include "PlayCppSdkActor.h"
#include "Utlis.h"

// Called when the game starts or when spawned
void ASendEthTransaction::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &ASendEthTransaction::OnSendEthTransactionBeginOverlap);
}

void ASendEthTransaction::OnSendEthTransactionBeginOverlap(
    UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult &SweepResult) {
    MetaverseCharacter = Cast<AMetaverseCharacter>(OtherActor);
    if (MetaverseCharacter->GetAccount().IsEmpty()) {
        MetaverseCharacter->SetAccount(
            FText::FromString(FString::Printf(TEXT("Plase scan QR Code"))));
    } else {
        MetaverseCharacter->SetAccount(MetaverseCharacter->GetAccount());
    }

    UWalletConnectTriggerComponent *WalletConnectTriggerComponent =
        GetWalletConnectTriggerComponent();

    WalletConnectTriggerComponent->OnWalletconnectSendEip155TransactionDelegate
        .BindDynamic(
            this,
            &ASendEthTransaction::OnWalletconnectSendEip155TransactionFinished);

    FWalletConnectTxEip155 tx;
    tx.to = FString("0xA914161b1b8d9dbC9c5310Fc7EBee5A5B18044b7");
    tx.value = FString("1000000000000000000");
    WalletConnectTriggerComponent->SendEip155Transaction(tx);

    WalletConnectTriggerComponent->OnShowQR.BindDynamic(this, &Super::ShowQR);
}

void ASendEthTransaction::OnWalletconnectSendEip155TransactionFinished(
    FWalletSendTXEip155Result SendResult) {
    UE_LOG(LogTemp, Log, TEXT("Transaction Hash: %s, Result: %s"),
           *UUtlis::ToHex(SendResult.tx_hash), *SendResult.result);
    // Update new balance
    // TODO Check transaction receipt before querying the balance
    if (MetaverseCharacter) {
        MetaverseCharacter->SetBalance(MetaverseCharacter->GetAccount());
    }
}
