// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Coin.generated.h"

class UPrimitiveComponent;
class UText3DComponent;
class USphereComponent;

UCLASS() class METAVERSE_API ACoin : public AActor {
  GENERATED_BODY()

private:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
            meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent *StaticMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
            meta = (AllowPrivateAccess = "true"))
  UText3DComponent *Text3D;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
            meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent *StaticMesh;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
            meta = (AllowPrivateAccess = "true"))
  USphereComponent *Sphere;

public:
  // Sets default values for this actor's properties
  ACoin();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UFUNCTION()
  void OnCoinBeginOverlap(UPrimitiveComponent *OverlappedComponent,
                          AActor *OtherActor, UPrimitiveComponent *OtherComp,
                          int32 OtherBodyIndex, bool bFromSweep,
                          const FHitResult &SweepResult);

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;
};
