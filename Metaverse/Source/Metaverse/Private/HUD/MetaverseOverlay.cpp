// Copyright 2022, Cronos Labs. All Rights Reserved


#include "HUD/MetaverseOverlay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMetaverseOverlay::SetBalance(float value) {
    BalanceText->SetText(FText::FromString(FString::Printf(TEXT("%f"), value)));
}
void UMetaverseOverlay::SetCoin(float value) {
    CoinText->SetText(FText::FromString(FString::Printf(TEXT("%f"), value)));
}
void UMetaverseOverlay::SetAccount(FText account) {
    AccountText->SetText(account);
}
