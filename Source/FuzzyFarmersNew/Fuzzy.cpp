// Fill out your copyright notice in the Description page of Project Settings.


#include "Fuzzy.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AFuzzy::AFuzzy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	captureCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CaptureCollision"));
	captureCollision->SetupAttachment(RootComponent);

	currentDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("CurrentDirection"));
	nextDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("NextDirection"));

	currentDirection->SetupAttachment(RootComponent);
	nextDirection->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AFuzzy::BeginPlay()
{
	Super::BeginPlay();

	fuzzyMesh = GetMesh();

	dmiMat = UMaterialInstanceDynamic::Create(fuzzyMat, this);
	fuzzyMesh->SetMaterial(0, dmiMat);
	dmiMat->SetVectorParameterValue("FuzzyColor", fuzzyColor);

	
}

void AFuzzy::LaunchTowardsPlayer()
{
	// Rotate arrow towards player
}

// Called every frame
void AFuzzy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}