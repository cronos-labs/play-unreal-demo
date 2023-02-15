// Copyright 2022, Cronos Labs. All Rights Reserved

#include "HUD/QROverlay.h"
#include "Components/Image.h"

void UQROverlay::ShowQR(UTexture2D *QRTexture) {
    if (QRImage) {
        QRImage->SetBrushFromTexture(QRTexture);
    }
}

void UQROverlay::HideQR() {
    if (QRImage) {
        QRImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
