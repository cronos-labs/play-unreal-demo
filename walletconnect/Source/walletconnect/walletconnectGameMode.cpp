// Copyright Epic Games, Inc. All Rights Reserved.

#include "walletconnectGameMode.h"
#include "walletconnectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AwalletconnectGameMode::AwalletconnectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
