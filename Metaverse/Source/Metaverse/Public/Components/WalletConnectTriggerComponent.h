// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "PlayCppSdkActor.h"
#include "WalletConnectTriggerComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FShowQR, UTexture2D *, Texture);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FHideQR, FString, Address, int64, ChainID);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class METAVERSE_API UWalletConnectTriggerComponent : public USphereComponent {
  GENERATED_BODY()
private:
  APlayCppSdkActor *_PlayCppSdk;

  APlayCppSdkActor *Setup();
  FString _SignPersonalMessage;
  FWalletConnectTxEip155 _WalletConnectTxEip155;

  FWalletconnectSignPersonalDelegate OnWalletconnectSignPersonalDelegate;
  UFUNCTION()
  void OnWalletconnectSignPersonalFinished(FWalletSignTXEip155Result SigningResult);

  FWalletconnectSignEip155TransactionDelegate OnWalletconnectSignEip155TransactionDelegate;
  UFUNCTION()
  void OnWalletconnectSignEip155TransactionFinished(
      FWalletSignTXEip155Result SigningResult);

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
  void OnNewSessionReadyConnectFinished(
      FWalletConnectEnsureSessionResult SessionResult, FString Result);

  UFUNCTION()
  void OnNewSessionReadySignPersonalFinished(
      FWalletConnectEnsureSessionResult SessionResult, FString Result);

  UFUNCTION()
  void OnNewSessionReadySignEip155TransactionFinished(
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
            meta = (DisplayName = "SignPersonal", Keywords = "WalletConnect"),
            Category = "WalletConnect")
  void SignPersonal(FString message);

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "SignEip155Transaction",
                    Keywords = "WalletConnect"),
            Category = "WalletConnect")
  void SignEip155Transaction(FWalletConnectTxEip155 info);

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletConnect")
  FShowQR OnShowQR;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletConnect")
  FHideQR OnHideQR;

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void
  TickComponent(float DeltaTime, ELevelTick TickType,
                FActorComponentTickFunction *ThisTickFunction) override;
};
