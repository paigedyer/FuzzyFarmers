// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawningManager.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API ASpawningManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawningManager();

	/*UFUNCTION()
	void GenerateFuzzy();*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AOakTree*> OakTrees;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ABush*> Bushes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AUnderground*> Undergrounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AGrass*> Grasses;

	UPROPERTY(EditAnywhere)
	int maxFuzziesPlaced = 7;

	class AOakTree* nextOTSpawn;
	class ABush* nextBSpawn;
	class AUnderground* nextUSpawn;
	class AGrass* nextGSpawn;

	UFUNCTION()
	void PlaceFuzzies();

	UFUNCTION()
	void PrepareOakTree();

	UFUNCTION()
	void PrepareBush();

	UFUNCTION()
	void PrepareGrass();

	UFUNCTION()
	void PrepareUnderground();

};
