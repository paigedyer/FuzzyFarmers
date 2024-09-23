// Fill out your copyright notice in the Description page of Project Settings.

#include "Bush.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ABush::ABush()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rayCastCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RaycastCollision"));
	rayCastCollision->OnComponentHit.AddDynamic(this, &ABush::OnHit);

	RootComponent = rayCastCollision;

	playerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerCollision"));
	playerCollision->SetupAttachment(rayCastCollision);

	bush = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BushMesh"));
	bush->SetupAttachment(rayCastCollision);

}

// Called when the game starts or when spawned
void ABush::BeginPlay()
{
	Super::BeginPlay();

	// Picks a random bush mesh from the list
	bush->SetStaticMesh(bushMeshses[FMath::RandRange(0, (bushMeshses.Num() - 1))]);

	leavesColor = GetRandColor();

	dmiMat = UMaterialInstanceDynamic::Create(bushMat, this);
	bush->SetMaterial(0, dmiMat);
	dmiMat->SetVectorParameterValue("BushColor", leavesColor);

}

// Called every frame
void ABush::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABush::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void ABush::FuzzyPrepared()
// For when a fuzzy is hiding in the object but hasn't been spawned yet.
{
	// Enable Sound
	// https://forums.unrealengine.com/t/how-to-get-a-random-number-in-range-c/721860/3
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABush::PlaySound, FMath::RandRange(soundTimeMin, soundTimeMax), true);

}

void ABush::PlaySound()
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
		LeavesBurst();
		playing = false;
	}
}

FLinearColor ABush::GetRandColor()
{
	float rMin = 0.f;
	float rMax = 0.036368f;
	float g = 0.078125f;
	float bMin = 0.006892f;
	float bMax = 0.01969f;

	FLinearColor tempColor = FLinearColor(FMath::RandRange(rMin, rMax), g, FMath::RandRange(bMin, bMax));
	return tempColor;
}

void ABush::LeavesBurst()
{
	UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(leavesBurst, bush, NAME_None, FVector(0.f, 0.f, 0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
	if (particleComp) {
		particleComp->SetNiagaraVariableLinearColor(FString("ParticleColor"), leavesColor);
		// Set a new random time
		int index = FMath::RandRange(0, (leavesSounds.Num()) - 1);
		UGameplayStatics::PlaySoundAtLocation(this, leavesSounds[index], GetActorLocation());
	}
}

void ABush::ContainsFuzzy()
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

