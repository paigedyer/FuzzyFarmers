// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "InputConfigData.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Look;

};