// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METAVERSE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttributeComponent();
    // Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void SetBalance(float value);
	void SetCoin(float value);
	void AddCoin(float value);
	void SetAccount(FText account);
    FORCEINLINE FText GetAccount() { return Account; };
	FORCEINLINE float GetBalance() {return Balance;};
	FORCEINLINE float GetCoin() {return Coin;};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FText Account;
	float Balance;
	float Coin;


};
