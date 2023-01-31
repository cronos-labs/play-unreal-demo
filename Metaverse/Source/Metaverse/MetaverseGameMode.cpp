// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetaverseGameMode.h"
#include "MetaverseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMetaverseGameMode::AMetaverseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
