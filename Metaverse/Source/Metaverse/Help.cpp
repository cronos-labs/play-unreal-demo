// Copyright 2022, Cronos Labs. All Rights Reserved


#include "Help.h"
#include "WalletConnectTriggerComponent.h"
#include "Text3DComponent.h"

// Sets default values
AHelp::AHelp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WalletConnectTrigger = CreateDefaultSubobject<UWalletConnectTriggerComponent>(TEXT("WalletConnect Trigger"));
	RootComponent = WalletConnectTrigger;


	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(WalletConnectTrigger);

	Text3D = CreateDefaultSubobject<UText3DComponent>(TEXT("Operation Message"));
	Text3D->SetupAttachment(BaseMesh);



}

// Called when the game starts or when spawned
void AHelp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHelp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
