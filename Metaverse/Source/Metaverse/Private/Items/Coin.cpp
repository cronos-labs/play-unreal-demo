// Copyright 2022, Cronos Labs. All Rights Reserved

#include "Items/Coin.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Text3DComponent.h"
#include "../../MetaverseCharacter.h"

// Sets default values
ACoin::ACoin() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  StaticMeshComponent =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
  RootComponent = StaticMeshComponent;
  Text3D = CreateDefaultSubobject<UText3DComponent>(TEXT("Text3D"));
  Text3D->SetupAttachment(StaticMeshComponent);
  StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
  StaticMesh->SetupAttachment(StaticMeshComponent);
  Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
  Sphere->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay() {
  Super::BeginPlay();
  Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnCoinBeginOverlap);
}

// Called every frame
void ACoin::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ACoin::OnCoinBeginOverlap(UPrimitiveComponent *OverlappedComponent,
                               AActor *OtherActor,
                               UPrimitiveComponent *OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult &SweepResult) {
  AMetaverseCharacter* MetaverseCharacter = Cast<AMetaverseCharacter>(OtherActor);
  MetaverseCharacter->AddCoin(1);
  Destroy();
}
