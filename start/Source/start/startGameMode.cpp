// Copyright Epic Games, Inc. All Rights Reserved.

#include "startGameMode.h"
#include "startCharacter.h"
#include "UObject/ConstructorHelpers.h"

AstartGameMode::AstartGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
