// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DefiWalletCoreComponent.generated.h"

class ADefiWalletCoreActor;

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class METAVERSE_API UDefiWalletCoreComponent : public UActorComponent {
    GENERATED_BODY()
  public:
    UDefiWalletCoreComponent();
    // Called every frame
    virtual void
    TickComponent(float DeltaTime, ELevelTick TickType,
                  FActorComponentTickFunction *ThisTickFunction) override;
    FORCEINLINE ADefiWalletCoreActor *GetDefiWalletCore() {
        return _DefiWalletCore;
    }
    void Setup();

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;

  private:
    ADefiWalletCoreActor *_DefiWalletCore;
};
