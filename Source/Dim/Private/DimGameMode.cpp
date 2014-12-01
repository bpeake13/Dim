// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Dim.h"
#include "DimGameMode.h"
#include "DimPlayerController.h"
#include "DimCharacter.h"

ADimGameMode::ADimGameMode(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
{
	// use our custom PlayerController class
	PlayerControllerClass = ADimPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}