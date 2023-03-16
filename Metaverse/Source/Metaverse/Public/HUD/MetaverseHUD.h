// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MetaverseHUD.generated.h"

class UMetaverseOverlay;
class UQROverlay;

/**
 *
 */
UCLASS() class METAVERSE_API AMetaverseHUD : public AHUD {
    GENERATED_BODY()
  protected:
    virtual void BeginPlay() override;

  private:
    UPROPERTY(EditDefaultsOnly, Category = Metaverse)
    TSubclassOf<UMetaverseOverlay> MetaverseOverlayClass;
    UPROPERTY()
    UMetaverseOverlay *MetaverseOverlay;
    UPROPERTY(EditDefaultsOnly, Category = Metaverse)
    TSubclassOf<UQROverlay> QROverlayClass;
    UPROPERTY()
    UQROverlay *QROverlay;

  public:
    UMetaverseOverlay *GetMetaverseOverlay();
    UQROverlay *GetQROverlay();
    void ShowQR(UTexture2D *QRTexture);
    void HideQR();
};
