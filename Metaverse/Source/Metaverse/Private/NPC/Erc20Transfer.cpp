// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/Erc20Transfer.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"
#include "PlayCppSdkActor.h"
#include "Utlis.h"

// Called when the game starts or when spawned
void AErc20Transfer::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &AErc20Transfer::OnErc20TransferBeginOverlap);
}

void AErc20Transfer::OnErc20TransferBeginOverlap(
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

    WalletConnectTriggerComponent->OnCronosSendContractTransactionDelegate
        .BindDynamic(this,
                     &AErc20Transfer::OnWalletconnectErc20TranferFinished);

    WalletConnectTriggerComponent->Erc20Transfer(
        "0xC213a7B37F4f7eC81f78895E50EA773aA8E78255",
        "0xA914161b1b8d9dbC9c5310Fc7EBee5A5B18044b7", "1000000000000000000", "", "");

    WalletConnectTriggerComponent->OnShowQR.BindDynamic(this, &Super::ShowQR);
}

void AErc20Transfer::OnWalletconnectErc20TranferFinished(
    FWalletSendTXEip155Result TxResult) {
    UE_LOG(LogTemp, Log, TEXT("Transaction Hash: %s, Result: %s"),
           *UUtlis::ToHex(TxResult.tx_hash), *TxResult.result);
    // Update new balance
    // TODO Check transaction receipt before querying the balance
    if (MetaverseCharacter) {
        MetaverseCharacter->WaitForTransactionReceipt(TxResult.tx_hash);
        //TODO check receipt valid or not
    }
}
