// Copyright 2022, Cronos Labs. All Rights Reserved

#include "Components/AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent() {
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UAttributeComponent::BeginPlay() {
    Super::BeginPlay();

    // ...
}

// Called every frame
void UAttributeComponent::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UAttributeComponent::SetCoin(float value) { Coin = value; }
void UAttributeComponent::SetBalance(float value) { Balance = value; }
void UAttributeComponent::AddCoin(float value) { Coin += value; }

void UAttributeComponent::SetAccount(FText account) { Account = account; }
