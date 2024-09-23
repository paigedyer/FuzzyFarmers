// Fill out your copyright notice in the Description page of Project Settings.


#include "TestNiagaraSpaner.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATestNiagaraSpaner::ATestNiagaraSpaner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rayCastCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RaycastCollision"));

	RootComponent = rayCastCollision;

	dirtMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DirtMesh"));
	dirtMesh->SetupAttachment(rayCastCollision);
	// TODO: Set no collision on Static Mesh
}

// Called when the game starts or when spawned
void ATestNiagaraSpaner::BeginPlay()
{

	dmiMat = UMaterialInstanceDynamic::Create(dirtMat, this);
	dirtMesh->SetMaterial(0, dmiMat);
	dmiMat->SetVectorParameterValue("SpawnpointColor", dirtMeshColor);

	ContainsFuzzy();
	
}

void ATestNiagaraSpaner::DirtBurst()
{
	UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(dirtParticle, dirtMesh, NAME_None, FVector(0.f, 0.f, 0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
	if (particleComp) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("BURST"));
		particleComp->SetNiagaraVariableLinearColor(FString("ParticleColor"), dirtMeshColor);
		// Orient upwards
		particleComp->SetNiagaraVariableVec3(FString("Orientation"), FVector(0.f, 0.f, 50.f));
		particleComp->SetNiagaraVariableVec3(FString("Offset"), FVector(0.f, 0.f, 10.f));
		// Set a new random time
		int index = FMath::RandRange(0, (dirtSounds.Num()) - 1);
		UGameplayStatics::PlaySoundAtLocation(this, dirtSounds[index], GetActorLocation());
	}

}
void ATestNiagaraSpaner::ContainsFuzzy()
{
	if (!containsFuzzy)
	{
		containsFuzzy = true;
		FuzzyPrepared();
	}
	else
	{
		containsFuzzy = false;
	}
}

void ATestNiagaraSpaner::FuzzyPrepared()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATestNiagaraSpaner::PlaySound, FMath::RandRange(soundTimeMin, soundTimeMax), true);
}

void ATestNiagaraSpaner::PlaySound()
{
	if (!playing)
	{
		// Pick a random Fuzzy sound from the list
		// Plays Fuzzy Sound at the location of the root component (raycastcollision)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fuzzy Sound"));
		playing = true;
		UGameplayStatics::PlaySoundAtLocation(this, fuzzySounds[FMath::RandRange(0, (fuzzySounds.Num()) - 1)], GetActorLocation());
	}
	else
	{
		DirtBurst();
		playing = false;
	}
}

