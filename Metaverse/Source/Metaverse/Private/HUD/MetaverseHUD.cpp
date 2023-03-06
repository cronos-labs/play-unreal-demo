// Copyright 2022, Cronos Labs. All Rights Reserved


#include "HUD/MetaverseHUD.h"
#include "HUD/MetaverseOverlay.h"
#include "HUD/QROverlay.h"
#include "Templates/Casts.h"

void AMetaverseHUD::BeginPlay() {
    Super::BeginPlay();
    UWorld* World = GetWorld();
    APlayerController* Controller = World->GetFirstPlayerController();
    MetaverseOverlay =
        CreateWidget<UMetaverseOverlay>(Controller, MetaverseOverlayClass);
    MetaverseOverlay->AddToViewport();
}
UMetaverseOverlay *AMetaverseHUD::GetMetaverseOverlay() {
    return MetaverseOverlay;
}

UQROverlay *AMetaverseHUD::GetQROverlay() {
    return QROverlay;
}

void AMetaverseHUD::ShowQR(UTexture2D *QRTexture) {
    UWorld *World = GetWorld();
    APlayerController *Controller = World->GetFirstPlayerController();
    QROverlay = CreateWidget<UQROverlay>(Controller, QROverlayClass);
    QROverlay->ShowQR(QRTexture);
    QROverlay->AddToViewport();
}

void AMetaverseHUD::HideQR() {
    if (QROverlay) {
        QROverlay->HideQR();
    }
}
