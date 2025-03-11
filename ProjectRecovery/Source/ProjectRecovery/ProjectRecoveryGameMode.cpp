// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectRecoveryGameMode.h"
#include "ProjectRecoveryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectRecoveryGameMode::AProjectRecoveryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
