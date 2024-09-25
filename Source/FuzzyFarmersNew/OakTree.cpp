// Fill out your copyright notice in the Description page of Project Settings.


#include "OakTree.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values
AOakTree::AOakTree()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rayCastCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RaycastCollision"));
	rayCastCollision->OnComponentHit.AddDynamic(this, &AOakTree::OnHit);

	RootComponent = rayCastCollision;

	playerCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCollision"));

	playerCollision->SetupAttachment(rayCastCollision);

	treeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrunkMesh"));

	treeMesh->SetupAttachment(rayCastCollision);

	arrowcomponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	arrowcomponent->SetupAttachment(treeMesh);

}

// Called when the game starts or when spawned
void AOakTree::BeginPlay()
{
	Super::BeginPlay();

	leavesColor = GetRandColor();

	dmiMat = UMaterialInstanceDynamic::Create(leavesMat, this);
	treeMesh->SetMaterial(1, dmiMat);
	dmiMat->SetVectorParameterValue("SpawnpointColor", leavesColor);

	arrowRotation = arrowcomponent->GetComponentRotation();	// World Space!

}

// Called every frame
void AOakTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOakTree::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AOakTree::LeavesBurst()
{
	FRotator minRot = arrowRotation - FRotator(10.f, 10.f, 10.f);
	FRotator maxRot = arrowRotation - FRotator(10.f, 10.f, 10.f);
	float rot = FMath::RandRange(minRot.Pitch, maxRot.Pitch);
	float yaw = FMath::RandRange(minRot.Yaw, maxRot.Yaw);
	float roll = FMath::RandRange(minRot.Roll, maxRot.Roll);


	// Unsure if this will reduce performance, I doubt it but I can remove it if it's too much.
	FRotator rotation = FRotator(rot, yaw, roll);

	UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(leavesBurst, treeMesh, NAME_None, FVector(0.f, 0.f, 0.f), rotation, EAttachLocation::KeepRelativeOffset, true);
	if (particleComp) {
		particleComp->SetNiagaraVariableLinearColor(FString("ParticleColor"), leavesColor);

		// Set a new random time
		int index = FMath::RandRange(0, (leavesSounds.Num()) - 1);
		UGameplayStatics::PlaySoundAtLocation(this, leavesSounds[index], GetActorLocation());
	}
}

void AOakTree::ContainsFuzzy()
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

void AOakTree::FuzzyPrepared()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOakTree::PlaySound, FMath::RandRange(soundTimeMin, soundTimeMax), true);
}

void AOakTree::PlaySound()
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

FLinearColor AOakTree::GetRandColor()
{
	// Picks a random color from the list of colors provided in the Blueprint
	FLinearColor color = leavesColors[FMath::RandRange((0), (leavesColors.Num() - 1))];
	return color;
}