// Copyright Epic Games, Inc. All Rights Reserved.

#include "StudyGameMode.h"
#include "StudyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStudyGameMode::AStudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
