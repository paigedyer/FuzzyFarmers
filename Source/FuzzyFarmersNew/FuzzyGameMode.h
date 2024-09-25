// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FuzzyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYFARMERSNEW_API AFuzzyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFuzzyGameMode();

protected:
	virtual void BeginPlay() override;
};
