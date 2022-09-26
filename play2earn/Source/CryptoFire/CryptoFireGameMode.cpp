// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptoFireGameMode.h"
#include "CryptoFireCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptoFireGameMode::ACryptoFireGameMode() : Super() {
  // set default pawn class to our Blueprinted character
  static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
      TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
  DefaultPawnClass = PlayerPawnClassFinder.Class;
}
