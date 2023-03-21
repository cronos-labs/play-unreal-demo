// Copyright 2022, Cronos Labs. All Rights Reserved

#include "Components/WalletConnectTriggerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utlis.h"

UWalletConnectTriggerComponent::UWalletConnectTriggerComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UWalletConnectTriggerComponent::BeginPlay() {

    Super::BeginPlay();

    UE_LOG(LogTemp, Display, TEXT("WalletConnect Trigger Commponent Alive"));

    OnWalletconnectSignPersonalDelegate.BindDynamic(
        this,
        &UWalletConnectTriggerComponent::OnWalletconnectSignPersonalFinished);
    OnWalletconnectSignEip155TransactionDelegate.BindDynamic(
        this, &UWalletConnectTriggerComponent::OnWalletconnectSignEip155TransactionFinished);
}

void UWalletConnectTriggerComponent::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//
// Common Functions
//
APlayCppSdkActor *UWalletConnectTriggerComponent::Setup() {
    APlayCppSdkActor *PlayCppSdk =
        (APlayCppSdkActor *)UGameplayStatics::GetActorOfClass(
            GetWorld(), APlayCppSdkActor::StaticClass());

    FString description = "Defi WalletConnect example.";
    FString url = "http://localhost:8080/";
    TArray<FString> icon_urls;
    FString name = "New Defi WalletConnect Web3 Example";
    int64 chain_id = 25;
    EConnectionType connection_type = EConnectionType::QR_TEXTURE;

    if (PlayCppSdk) {
        UE_LOG(LogTemp, Display, TEXT("%s was found, walletconnect status: %s"),
               *PlayCppSdk->GetActorNameOrLabel(),
               *UEnum::GetValueAsString(
                   PlayCppSdk->GetWalletConnectSessionInfo().sessionstate))
        switch (PlayCppSdk->GetWalletConnectSessionInfo().sessionstate) {
        case EWalletconnectSessionState::StateConnecting:
            break;
        case EWalletconnectSessionState::StateConnected:
            break;
        case EWalletconnectSessionState::StateUpdated:
            break;
        case EWalletconnectSessionState::StateInit:
        case EWalletconnectSessionState::StateDisconnected: {
            PlayCppSdk->ConnectWalletConnect(description, url, icon_urls, name,
                                             chain_id, connection_type);
            break;
        }
        case EWalletconnectSessionState::StateRestored:
            break;
        default:
            break;
        }
    } else {
        APlayCppSdkActor *NewPlayCppSdk =
            (APlayCppSdkActor *)GetWorld()->SpawnActor(
                APlayCppSdkActor::StaticClass());
        NewPlayCppSdk->ConnectWalletConnect(description, url, icon_urls, name,
                                            chain_id, connection_type);
        UE_LOG(LogTemp, Display, TEXT("%s was created"),
               *NewPlayCppSdk->GetActorNameOrLabel());
        return NewPlayCppSdk;
    }
    return PlayCppSdk;
}

void UWalletConnectTriggerComponent::OnQRReadyFinished(UTexture2D *Texture) {
    // Show QR
    this->OnShowQR.ExecuteIfBound(Texture);
}

void UWalletConnectTriggerComponent::
    OnReceiveWalletconnectSessionInfoDelegateFinished(
        FWalletConnectSessionInfo SessionInfo) {
    // Monitor the walletconnect events
    UE_LOG(LogTemp, Display, TEXT("Got %s event: %s"),
           *_PlayCppSdk->GetActorNameOrLabel(),
           *UEnum::GetValueAsString(SessionInfo.sessionstate))
    switch (SessionInfo.sessionstate) {
    case EWalletconnectSessionState::StateConnecting:
        break;
    case EWalletconnectSessionState::StateConnected:
        break;
    case EWalletconnectSessionState::StateUpdated:
        break;
    case EWalletconnectSessionState::StateDisconnected:
        break;
    default:
        break;
    }
}

//
// Connect
//
void UWalletConnectTriggerComponent::Connect() {

    _PlayCppSdk = this->Setup();

    UE_LOG(LogTemp, Display, TEXT("%s walletconnect status: %s"),
           *_PlayCppSdk->GetActorNameOrLabel(),
           *UEnum::GetValueAsString(
               _PlayCppSdk->GetWalletConnectSessionInfo().sessionstate))
    switch (_PlayCppSdk->GetWalletConnectSessionInfo().sessionstate) {
    case EWalletconnectSessionState::StateInit:
    case EWalletconnectSessionState::StateDisconnected: {

        _PlayCppSdk->OnRestoreSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnRestoreSessionReadyConnectFinished);

        _PlayCppSdk->OnNewSessionReady.BindDynamic(
            this,
            &UWalletConnectTriggerComponent::OnNewSessionReadyConnectFinished);

        _PlayCppSdk->OnQRReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnQRReadyFinished);

        _PlayCppSdk->OnReceiveWalletconnectSessionInfoDelegate.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnReceiveWalletconnectSessionInfoDelegateFinished);

        break;
    }
    case EWalletconnectSessionState::StateConnecting:
        break;
    case EWalletconnectSessionState::StateConnected:
    case EWalletconnectSessionState::StateUpdated:
        break;
    case EWalletconnectSessionState::StateRestored:
        break;
    default:
        break;
    }
}

void UWalletConnectTriggerComponent::OnRestoreSessionReadyConnectFinished(
    FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    UE_LOG(LogTemp, Log,
           TEXT("OnRestoreSession Account[0]: %s, Chain id: %d, Result: %s"),
           SessionResult.addresses.Num() > 0
               ? *UUtlis::ToHex(SessionResult.addresses[0].address)
               : *FString("No Addresses"),
           SessionResult.chain_id, *Result);
}

void UWalletConnectTriggerComponent::OnNewSessionReadyConnectFinished(
    FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    FString address = SessionResult.addresses.Num() > 0
                          ? UUtlis::ToHex(SessionResult.addresses[0].address)
                          : FString("No Addresses");
    int64 chain_id = SessionResult.chain_id;
    UE_LOG(LogTemp, Log,
           TEXT("OnRestoreSession Account[0]: %s, Chain id: %d, Result: %s"),
           *address, chain_id, *Result);
    // Hide QR
    this->OnHideQRAndUpdateOverlay.ExecuteIfBound(address, chain_id);
}

//
// SignPersonal
//
void UWalletConnectTriggerComponent::SignPersonal(FString message) {

    _PlayCppSdk = this->Setup();
    _SignPersonalMessage = message;

    UE_LOG(LogTemp, Display, TEXT("%s walletconnect status: %s"),
           *_PlayCppSdk->GetActorNameOrLabel(),
           *UEnum::GetValueAsString(
               _PlayCppSdk->GetWalletConnectSessionInfo().sessionstate))
    switch (_PlayCppSdk->GetWalletConnectSessionInfo().sessionstate) {
    case EWalletconnectSessionState::StateInit:
    case EWalletconnectSessionState::StateDisconnected: {

        _PlayCppSdk->OnRestoreSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnRestoreSessionReadySignPersonalFinished);

        _PlayCppSdk->OnNewSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnNewSessionReadySignPersonalFinished);

        _PlayCppSdk->OnQRReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnQRReadyFinished);

        break;
    }
    case EWalletconnectSessionState::StateConnecting:
        break;
    case EWalletconnectSessionState::StateConnected:
    case EWalletconnectSessionState::StateRestored:
    case EWalletconnectSessionState::StateUpdated: {

        _PlayCppSdk->SignPersonal(message, OnWalletconnectSignPersonalDelegate);

        break;
    }
    default:
        break;
    }
}

void UWalletConnectTriggerComponent::OnWalletconnectSignPersonalFinished(
    FWalletSignTXEip155Result SigningResult) {
    UE_LOG(LogTemp, Log, TEXT("Signing Signature: %s, Result: %s"),
           *UUtlis::ToHex(SigningResult.signature), *SigningResult.result);
}

void UWalletConnectTriggerComponent::OnRestoreSessionReadySignPersonalFinished(
    FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    UE_LOG(LogTemp, Log,
           TEXT("OnRestoreSession Account[0]: %s, Chain id: %d, Result: %s"),
           SessionResult.addresses.Num() > 0
               ? *UUtlis::ToHex(SessionResult.addresses[0].address)
               : *FString("No Addresses"),
           SessionResult.chain_id, *Result);

    // Sign Personal
    _PlayCppSdk->SignPersonal(_SignPersonalMessage,
                              OnWalletconnectSignPersonalDelegate);
}

void UWalletConnectTriggerComponent::OnNewSessionReadySignPersonalFinished(
    FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    FString address = SessionResult.addresses.Num() > 0
                          ? UUtlis::ToHex(SessionResult.addresses[0].address)
                          : FString("No Addresses");
    int64 chain_id = SessionResult.chain_id;
    UE_LOG(LogTemp, Log,
           TEXT("OnNewSession Account[0]: %s, Chain id: %d, Result: %s"),
           *address, chain_id, *Result);
    // Hide QR
    this->OnHideQRAndUpdateOverlay.ExecuteIfBound(address, chain_id);

    // Sign Personal
    _PlayCppSdk->SignPersonal(_SignPersonalMessage,
                              OnWalletconnectSignPersonalDelegate);
}

//
// SignEip155Transaction
//
void UWalletConnectTriggerComponent::SignEip155Transaction(
    FWalletConnectTxEip155 info) {

    _PlayCppSdk = this->Setup();
    _WalletConnectTxEip155 = info; // set the interal value

    UE_LOG(LogTemp, Display, TEXT("%s walletconnect status: %s"),
           *_PlayCppSdk->GetActorNameOrLabel(),
           *UEnum::GetValueAsString(
               _PlayCppSdk->GetWalletConnectSessionInfo().sessionstate))
    switch (_PlayCppSdk->GetWalletConnectSessionInfo().sessionstate) {
    case EWalletconnectSessionState::StateInit:
    case EWalletconnectSessionState::StateDisconnected: {

        _PlayCppSdk->OnRestoreSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnRestoreSessionReadySignEip155TransactionFinished);

        _PlayCppSdk->OnNewSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnNewSessionReadySignEip155TransactionFinished);

        _PlayCppSdk->OnQRReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnQRReadyFinished);

        break;
    }
    case EWalletconnectSessionState::StateConnecting:
        break;
    case EWalletconnectSessionState::StateConnected:
    case EWalletconnectSessionState::StateRestored:
    case EWalletconnectSessionState::StateUpdated: {

        _PlayCppSdk->SignEip155Transaction(
            info, OnWalletconnectSignEip155TransactionDelegate);

        break;
    }
    default:
        break;
    }
}

void UWalletConnectTriggerComponent::
    OnWalletconnectSignEip155TransactionFinished(
        FWalletSignTXEip155Result SigningResult) {
    UE_LOG(LogTemp, Log, TEXT("Signing Signature: %s, Result: %s"),
           *UUtlis::ToHex(SigningResult.signature), *SigningResult.result);
}

void UWalletConnectTriggerComponent::
    OnRestoreSessionReadySignEip155TransactionFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    UE_LOG(LogTemp, Log,
           TEXT("OnRestoreSession Account[0]: %s, Chain id: %d, Result: %s"),
           SessionResult.addresses.Num() > 0
               ? *UUtlis::ToHex(SessionResult.addresses[0].address)
               : *FString("No Addresses"),
           SessionResult.chain_id, *Result);

    // Sign Eip155
    _PlayCppSdk->SignEip155Transaction(
        _WalletConnectTxEip155, OnWalletconnectSignEip155TransactionDelegate);
}

void UWalletConnectTriggerComponent::
    OnNewSessionReadySignEip155TransactionFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    FString address = SessionResult.addresses.Num() > 0
                          ? UUtlis::ToHex(SessionResult.addresses[0].address)
                          : FString("No Addresses");
    int64 chain_id = SessionResult.chain_id;
    UE_LOG(LogTemp, Log,
           TEXT("OnNewSession Account[0]: %s, Chain id: %d, Result: %s"),
           *address, chain_id, *Result);
    // Hide QR
    this->OnHideQRAndUpdateOverlay.ExecuteIfBound(address, chain_id);

    // SignEip155Transaction
    _PlayCppSdk->SignEip155Transaction(
        _WalletConnectTxEip155, OnWalletconnectSignEip155TransactionDelegate);
}

//
// Disconnect
//
void UWalletConnectTriggerComponent::Disconnect() {
    _PlayCppSdk = (APlayCppSdkActor *)UGameplayStatics::GetActorOfClass(
        GetWorld(), APlayCppSdkActor::StaticClass());
    if (!_PlayCppSdk) {
        _PlayCppSdk = (APlayCppSdkActor *)GetWorld()->SpawnActor(
            APlayCppSdkActor::StaticClass());
    }

    bool success;
    _PlayCppSdk->ClearSession(success);
    if (success) {
        // Hide QR if any
        this->OnHideQR.ExecuteIfBound();
    } else {
        UE_LOG(LogTemp, Error,
               TEXT("Clear Session Failed. Please try to clear again."));
    }
}
