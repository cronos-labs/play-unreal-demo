// Copyright 2022, Cronos Labs. All Rights Reserved
// clang-format off
#include "Components/WalletConnectTriggerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utlis.h"

UWalletConnectTriggerComponent::UWalletConnectTriggerComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UWalletConnectTriggerComponent::BeginPlay() {

    Super::BeginPlay();

    UE_LOG(LogTemp, Display, TEXT("WalletConnect Trigger Commponent Alive"));
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

    
    std::string userrelayserver="wss://relay.walletconnect.com";
    std::string userprojectid="";
    std::string userwalletnamespace =
    "{\"eip155\":{\"methods\":[\"eth_sendTransaction\",\"eth_"
    "signTransaction\",\"eth_sign\",\"personal_sign\",\"eth_"
    "signTypedData\"],\"chains\":[\"eip155:5\"],\"events\":["
    "\"chainChanged\",\"accountsChanged\"]}}";
    std::string userclientmeta=
    "{\"description\":\"Defi WalletConnect v2 "
    "example.\",\"url\":\"http://localhost:8080/"
    "\",\"icons\":[],\"name\":\"Defi WalletConnect Web3 Example\"}";

    const char* projectId = std::getenv("NEXT_PUBLIC_PROJECT_ID");
        if (projectId != nullptr) {
            userprojectid = projectId;
        }
        // print projectid to unreal 
        UE_LOG(LogTemp, Display, TEXT("NEXT_PUBLIC_PROJECT_ID: %s"),
               UTF8_TO_TCHAR(userprojectid.c_str()));


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
            PlayCppSdk->ConnectWalletConnect(
        UTF8_TO_TCHAR(userrelayserver.c_str()),
        UTF8_TO_TCHAR(userprojectid.c_str()),
        UTF8_TO_TCHAR(userwalletnamespace.c_str()),
        UTF8_TO_TCHAR(userclientmeta.c_str()),
        connection_type);
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

        NewPlayCppSdk->OnReceiveWalletconnectPollingDelegate.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnReceiveWalletconnectPolling);

        NewPlayCppSdk->PollingEventsEnabled=true;
        NewPlayCppSdk->ConnectWalletConnect(  
        UTF8_TO_TCHAR(userrelayserver.c_str()),
        UTF8_TO_TCHAR(userprojectid.c_str()),
        UTF8_TO_TCHAR(userwalletnamespace.c_str()),
        UTF8_TO_TCHAR(userclientmeta.c_str()),
        connection_type);
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


void UWalletConnectTriggerComponent::OnReceiveWalletconnectPolling(FString jsonevent,
                                                     FString result) {

    // if result is empty, print log
    if (result.IsEmpty()) {
        UE_LOG(LogTemp, Log, TEXT("App ReceiveEvent= %s"), *jsonevent);
    }

    _PlayCppSdk->BeginPolling(_PlayCppSdk->OnReceiveWalletconnectPollingDelegate);
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
// SendEip155Transaction
//
void UWalletConnectTriggerComponent::SendEip155Transaction(
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
            this, &UWalletConnectTriggerComponent::OnRestoreSessionReadySendEip155TransactionFinished);

        _PlayCppSdk->OnNewSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnNewSessionReadySendEip155TransactionFinished);

        _PlayCppSdk->OnQRReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnQRReadyFinished);

        break;
    }
    case EWalletconnectSessionState::StateConnecting:
        break;
    case EWalletconnectSessionState::StateConnected:
    case EWalletconnectSessionState::StateRestored:
    case EWalletconnectSessionState::StateUpdated: {

        _PlayCppSdk->SendEip155Transaction(
            info, OnWalletconnectSendEip155TransactionDelegate);

        break;
    }
    default:
        break;
    }
}

void UWalletConnectTriggerComponent::
    OnRestoreSessionReadySendEip155TransactionFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    UE_LOG(LogTemp, Log,
           TEXT("OnRestoreSession Account[0]: %s, Chain id: %d, Result: %s"),
           SessionResult.addresses.Num() > 0
               ? *UUtlis::ToHex(SessionResult.addresses[0].address)
               : *FString("No Addresses"),
           SessionResult.chain_id, *Result);

    // Send Eip155
    _PlayCppSdk->SendEip155Transaction(
        _WalletConnectTxEip155, OnWalletconnectSendEip155TransactionDelegate);
}

void UWalletConnectTriggerComponent::
    OnNewSessionReadySendEip155TransactionFinished(
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

    // SendEip155Transaction
    _PlayCppSdk->SendEip155Transaction(
        _WalletConnectTxEip155, OnWalletconnectSendEip155TransactionDelegate);
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

//
// Erc20Transfer
//
void UWalletConnectTriggerComponent::Erc20Transfer(
    FString contractAddress, FString toAddress, FString amount,
    FString gasLimit, FString gasPrice) {

    _PlayCppSdk = this->Setup();
    // set the interal values
    _contractAddress = contractAddress;
    _toAddress = toAddress;
    _amount = amount;
    _gasLimit = gasLimit;
    _gasPrice = gasPrice;

    UE_LOG(LogTemp, Display, TEXT("%s walletconnect status: %s"),
           *_PlayCppSdk->GetActorNameOrLabel(),
           *UEnum::GetValueAsString(
               _PlayCppSdk->GetWalletConnectSessionInfo().sessionstate))
    switch (_PlayCppSdk->GetWalletConnectSessionInfo().sessionstate) {
    case EWalletconnectSessionState::StateInit:
    case EWalletconnectSessionState::StateDisconnected: {

        _PlayCppSdk->OnRestoreSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnRestoreSessionErc20TransferFinished);

        _PlayCppSdk->OnNewSessionReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnNewSessionReadyErc20TranferFinished);

        _PlayCppSdk->OnQRReady.BindDynamic(
            this, &UWalletConnectTriggerComponent::OnQRReadyFinished);

        break;
    }
    case EWalletconnectSessionState::StateConnecting:
        break;
    case EWalletconnectSessionState::StateConnected:
    case EWalletconnectSessionState::StateRestored:
    case EWalletconnectSessionState::StateUpdated: {

        _PlayCppSdk->Erc20Transfer(contractAddress, toAddress, amount, gasLimit, gasPrice, OnCronosSendContractTransactionDelegate);

        break;
    }
    default:
        break;
    }
}

void UWalletConnectTriggerComponent::
    OnRestoreSessionErc20TransferFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result) {
    UE_LOG(LogTemp, Log,
           TEXT("OnRestoreSession Account[0]: %s, Chain id: %d, Result: %s"),
           SessionResult.addresses.Num() > 0
               ? *UUtlis::ToHex(SessionResult.addresses[0].address)
               : *FString("No Addresses"),
           SessionResult.chain_id, *Result);

        _PlayCppSdk->Erc20Transfer(_contractAddress, _toAddress, _amount, _gasLimit, _gasPrice, OnCronosSendContractTransactionDelegate);
}

void UWalletConnectTriggerComponent::
    OnNewSessionReadyErc20TranferFinished(
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

        _PlayCppSdk->Erc20Transfer(_contractAddress, _toAddress, _amount, _gasLimit, _gasPrice, OnCronosSendContractTransactionDelegate);
}

// clang-format on
