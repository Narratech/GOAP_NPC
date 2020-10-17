// Copyright Epic Games, Inc. All Rights Reserved.

#include "GOAPGameMode.h"
#include "GOAPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGOAPGameMode::AGOAPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
