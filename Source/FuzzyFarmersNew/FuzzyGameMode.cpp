// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzyGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"

AFuzzyGameMode::AFuzzyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	
}

void AFuzzyGameMode::BeginPlay()
{
	Super::BeginPlay();
}

