// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "PlayCppSdkActor.h"
#include "WalletConnectTriggerComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FShowQR, UTexture2D *, Texture);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FHideQRAndUpdateOverlay, FString, Address,
                                   int64, ChainID);
DECLARE_DYNAMIC_DELEGATE(FHideQR);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class METAVERSE_API UWalletConnectTriggerComponent : public USphereComponent {
    GENERATED_BODY()
  private:
    APlayCppSdkActor *_PlayCppSdk;

    APlayCppSdkActor *Setup();
    FString _SignPersonalMessage;
    FWalletConnectTxEip155 _WalletConnectTxEip155;
    FString _contractAddress;
    FString _toAddress;
    FString _amount;
    FString _gasLimit;
    FString _gasPrice;

    UFUNCTION()
    void OnRestoreSessionReadyConnectFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnRestoreSessionReadySignPersonalFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnRestoreSessionReadySignEip155TransactionFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnRestoreSessionReadySendEip155TransactionFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnRestoreSessionErc20TransferFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnNewSessionReadyConnectFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnNewSessionReadySignPersonalFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnNewSessionReadySignEip155TransactionFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnNewSessionReadySendEip155TransactionFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnNewSessionReadyErc20TranferFinished(
        FWalletConnectEnsureSessionResult SessionResult, FString Result);

    UFUNCTION()
    void OnQRReadyFinished(UTexture2D *Texture);

    UFUNCTION()
    void OnReceiveWalletconnectSessionInfoDelegateFinished(
        FWalletConnectSessionInfo SessionInfo);

  public:
    UWalletConnectTriggerComponent();

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Connect", Keywords = "WalletConnect"),
              Category = "WalletConnect")
    void Connect();

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Disconnect", Keywords = "WalletConnect"),
              Category = "WalletConnect")
    void Disconnect();

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "SignPersonal", Keywords = "WalletConnect"),
              Category = "WalletConnect")
    void SignPersonal(FString message);

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "SignEip155Transaction",
                      Keywords = "WalletConnect"),
              Category = "WalletConnect")
    void SignEip155Transaction(FWalletConnectTxEip155 info);

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "SendEip155Transaction",
                      Keywords = "WalletConnect"),
              Category = "WalletConnect")
    void SendEip155Transaction(FWalletConnectTxEip155 info);

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Erc20Transfer",
                      Keywords = "WalletConnect"),
              Category = "WalletConnect")
    void Erc20Transfer(FString contractAddress, FString toAddress,
                       FString amount, FString gasLimit, FString gasPrice);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletConnect")
    FShowQR OnShowQR;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletConnect")
    FHideQRAndUpdateOverlay OnHideQRAndUpdateOverlay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletConnect")
    FHideQR OnHideQR;

    FWalletconnectSignPersonalDelegate OnWalletconnectSignPersonalDelegate;
    FWalletconnectSignEip155TransactionDelegate
        OnWalletconnectSignEip155TransactionDelegate;
    FWalletconnectSendEip155TransactionDelegate
        OnWalletconnectSendEip155TransactionDelegate;

    FCronosSendContractTransactionDelegate
        OnCronosSendContractTransactionDelegate;

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void
    TickComponent(float DeltaTime, ELevelTick TickType,
                  FActorComponentTickFunction *ThisTickFunction) override;
};
