// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningManager.h"
#include <random>
#include "Kismet/GameplayStatics.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Math/UnrealMathUtility.h"
#include "OakTree.h"
#include "Bush.h"
#include "Grass.h"
#include "Underground.h"

// Sets default values
ASpawningManager::ASpawningManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawningManager::BeginPlay()
{
	Super::BeginPlay();

	// Prepare the fuzzies in the randomly selected spawnpoints
	PlaceFuzzies();
}

// Called every frame
void ASpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// check current # of fuzzies prepared
	// when you capture one, lower the number
	// if num < max
	// PlaceFuzzies

}

void ASpawningManager::PlaceFuzzies()
{
	// Prepare spawnpoints until the max number of prepared fuzzies is reached
	while (currentNumFuzzies < maxFuzziesPlaced)
	{
		int tmp = FMath::RandRange(1, 4);
		// Choose a random number from 1-4 for a random spawnpoint
		currentNumFuzzies += 1;
		switch (tmp)
		{
		case 1:
			PrepareOakTree();
			break;
		case 2:
			PrepareBush();
			break;
		case 3:
			PrepareGrass();
			break;
		case 4:
			PrepareUnderground();
			break;
		}
	}
}

void ASpawningManager::PrepareOakTree()
{
	// Picks a random spawnpoint from the list
	nextOTSpawn = OakTrees[FMath::RandRange(0, (OakTrees.Num() - 1))];
	// Makes sure the reference is valid/not null
	if (nextOTSpawn)
	{
		// If the spawnpoint doesn't already contain a fuzzy
		if (!nextOTSpawn->containsFuzzy)
		{
			// Prepare the fuzzy and set containsFuzzy in the instance to true
			nextOTSpawn->ContainsFuzzy();
		}
	}
}

void ASpawningManager::PrepareBush()
{
	// Picks a random spawnpoint from the list
	nextBSpawn = Bushes[FMath::RandRange(0, (Bushes.Num() - 1))];
	// Makes sure the reference is valid/not null
	if (nextBSpawn)
	{
		// If the spawnpoint doesn't already contain a fuzzy
		if (!nextBSpawn->containsFuzzy)
		{
			// Prepare the fuzzy and set containsFuzzy in the instance to true
			nextBSpawn->ContainsFuzzy();
		}
	}
}

void ASpawningManager::PrepareGrass()
{
	// Picks a random spawnpoint from the list
	nextGSpawn = Grasses[FMath::RandRange(0, (Grasses.Num() - 1))];
	// Makes sure the reference is valid/not null
	if (nextGSpawn)
	{
		// If the spawnpoint doesn't already contain a fuzzy
		if (!nextGSpawn->containsFuzzy)
		{
			// Prepare the fuzzy and set containsFuzzy in the instance to true
			nextGSpawn->ContainsFuzzy();
		}
	}
}

void ASpawningManager::PrepareUnderground()
{
	// Picks a random spawnpoint from the list
	nextUSpawn = Undergrounds[FMath::RandRange(0, (Undergrounds.Num() - 1))];
	// Makes sure the reference is valid/not null
	if (nextUSpawn)
	{
		// If the spawnpoint doesn't already contain a fuzzy
		if (!nextUSpawn->containsFuzzy)
		{
			// Prepare the fuzzy and set containsFuzzy in the instance to true
			nextUSpawn->ContainsFuzzy();
		}
	}
}


