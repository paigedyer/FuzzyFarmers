// Fill out your copyright notice in the Description page of Project Settings.


#include "Underground.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AUnderground::AUnderground()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rayCastCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RaycastCollision"));
	rayCastCollision->OnComponentHit.AddDynamic(this, &AUnderground::OnHit);

	RootComponent = rayCastCollision;

	dirtMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DirtMesh"));
	dirtMesh->SetupAttachment(rayCastCollision);
	// TODO: Set no collision on Static Mesh

	arrowcomponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	arrowcomponent->SetupAttachment(dirtMesh);

}

// Called when the game starts or when spawned
void AUnderground::BeginPlay()
{
	Super::BeginPlay();

	dmiMat = UMaterialInstanceDynamic::Create(dirtMat, this);
	dirtMesh->SetMaterial(0, dmiMat);
	dmiMat->SetVectorParameterValue("SpawnpointColor", dirtMeshColor);

	arrowRotation = arrowcomponent->GetComponentRotation();	// World Space!
}

// Called every frame
void AUnderground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnderground::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AUnderground::DirtBurst()
{
	UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(dirtParticle, dirtMesh, NAME_None, FVector(0.f, 0.f, 0.f), arrowRotation, EAttachLocation::KeepRelativeOffset, true);
	if (particleComp) {
		particleComp->SetNiagaraVariableLinearColor(FString("ParticleColor"), dirtMeshColor);

		// Set a new random time
		int index = FMath::RandRange(0, (dirtSounds.Num()) - 1);
		UGameplayStatics::PlaySoundAtLocation(this, dirtSounds[index], GetActorLocation());
	}
}

void AUnderground::ContainsFuzzy()
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

void AUnderground::FuzzyPrepared()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AUnderground::PlaySound, FMath::RandRange(soundTimeMin, soundTimeMax), true);
}

void AUnderground::PlaySound()
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


