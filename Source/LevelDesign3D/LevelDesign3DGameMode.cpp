// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelDesign3DGameMode.h"
#include "GameHUD.h"
#include "LevelDesign3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALevelDesign3DGameMode::ALevelDesign3DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;

		HUDClass = AGameHUD::StaticClass();
	}
}
