// Fill out your copyright notice in the Description page of Project Settings.

#include "Bush.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"
#include "PlayerCharacter.h"
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

	arrowcomponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	arrowcomponent->SetupAttachment(bush);

	textComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	textComponent->SetupAttachment(bush);

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

	textComponent->SetRelativeLocation(FVector(0.f, 0.f, 15.f));
	textComponent->SetText(FText::FromString("E"));
	textComponent->SetHorizontalAlignment(EHTA_Center);
	textComponent->SetVerticalAlignment(EVRTA_TextCenter);
	textComponent->SetWorldSize(20.0f);
	textComponent->SetVisibility(false);
	

	if (dmiMat)
	{
		dmiMat->SetVectorParameterValue("SpawnpointColor", leavesColor);

	}
	arrowRotation = arrowcomponent->GetComponentRotation();	// World Space!

}

// Called every frame
void ABush::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Adjust rotation if active of textrender

}

void ABush::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FHitResult hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		UInteract_I* Interface = Cast<UInteract_I>(Hit.GetActor());
	}
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
		
		playing = true;
		int index = FMath::RandRange(0, (fuzzySounds.Num()) - 1);
		if (fuzzySounds.IsValidIndex(index))
		{
			UGameplayStatics::PlaySoundAtLocation(this, fuzzySounds[index], GetActorLocation());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid index in FuzzySounds!!"));

		}
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

void ABush::ActPressE(FVector start)
{
	bTRActive = true;
	textComponent->SetVisibility(true);
	FVector txtLoc = textComponent->GetComponentLocation();
	FRotator rotation = FRotator::MakeFromEuler(start - txtLoc);

	textComponent->SetRelativeRotation(rotation);
}

void ABush::LeavePoint()
{
	bTRActive = false;
	textComponent->SetVisibility(true);
}

void ABush::LeavesBurst()
{
	UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(leavesBurst, arrowcomponent, NAME_None, FVector(0.f, 0.f, 0.f), arrowRotation, EAttachLocation::KeepRelativeOffset, true);
	if (particleComp) {
		particleComp->SetNiagaraVariableLinearColor(FString("ParticleColor"), leavesColor);

		// Set a new random time
		int index = FMath::RandRange(0, (leavesSounds.Num()) - 1);
		if (leavesSounds.IsValidIndex(index)) 
		{
			UGameplayStatics::PlaySoundAtLocation(this, leavesSounds[index], GetActorLocation());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid index in LeavesSounds!!"));
		}
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

