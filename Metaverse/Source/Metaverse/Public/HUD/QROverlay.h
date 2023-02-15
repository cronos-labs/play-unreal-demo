// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QROverlay.generated.h"

class UImage;
/**
 *
 */
UCLASS()
class METAVERSE_API UQROverlay : public UUserWidget {
    GENERATED_BODY()
  public:
    void ShowQR(UTexture2D * QRTexture);
    void HideQR();

  private:
    UPROPERTY(meta = (BindWidget))
    UImage *QRImage;
};
