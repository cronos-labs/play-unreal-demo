// Copyright 2022, Cronos Labs. All Rights Reserved

#include "Components/DefiWalletCoreComponent.h"
#include "DefiWalletCoreActor.h"

UDefiWalletCoreComponent::UDefiWalletCoreComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UDefiWalletCoreComponent::BeginPlay() { Super::BeginPlay(); }

void UDefiWalletCoreComponent::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDefiWalletCoreComponent::Setup() {
    ADefiWalletCoreActor *DefiWalletCore =
        (ADefiWalletCoreActor *)UGameplayStatics::GetActorOfClass(
            GetWorld(), ADefiWalletCoreActor::StaticClass());

    if (DefiWalletCore) {
        UE_LOG(LogTemp, Display, TEXT("%s was found"),
               *DefiWalletCore->GetActorNameOrLabel());
    } else {
        ADefiWalletCoreActor *NewDefiWalletCore =
            (ADefiWalletCoreActor *)GetWorld()->SpawnActor(
                ADefiWalletCoreActor::StaticClass());
        // NewDefiWalletCore->myCronosChainID = 1;
        // NewDefiWalletCore->myCronosRpc =
        // "https://api.infura.io/v1/jsonrpc/mainnet";
        // NewDefiWalletCore->myCronosChainID = 25;
        // NewDefiWalletCore->myCronosRpc = "https://evm-dev.cronos.org/";
        NewDefiWalletCore->myCronosChainID = 338;
        NewDefiWalletCore->myCronosRpc = "https://evm-dev-t3.cronos.org";
        UE_LOG(LogTemp, Display, TEXT("%s was created"),
               *NewDefiWalletCore->GetActorNameOrLabel());
        _DefiWalletCore = NewDefiWalletCore;
        return;
    }
    _DefiWalletCore = DefiWalletCore;
}
