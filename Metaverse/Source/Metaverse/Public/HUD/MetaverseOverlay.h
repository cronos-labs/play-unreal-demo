// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MetaverseOverlay.generated.h"

class UTextBlock;
class UImage;
/**
 *
 */
UCLASS()
class METAVERSE_API UMetaverseOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetCoin(float value);
    void SetBalance(float value);
    void SetAccount(FText account);
private:
    UPROPERTY(meta = (BindWidget))
    UTextBlock *CoinText;
    UPROPERTY(meta = (BindWidget))
    UTextBlock *AccountText;
    UPROPERTY(meta = (BindWidget))
    UTextBlock *BalanceText;
    UPROPERTY(meta = (BindWidget))
    UImage *CoinImage;
    UPROPERTY(meta = (BindWidget))
    UImage *WalletConnectImage;
    UPROPERTY(meta = (BindWidget))
    UImage *BalanceImage;

};
