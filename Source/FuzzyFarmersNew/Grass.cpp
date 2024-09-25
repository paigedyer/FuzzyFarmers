// For grass spawnpoints


#include "Grass.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AGrass::AGrass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rayCastCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RaycastCollision"));
	rayCastCollision->OnComponentHit.AddDynamic(this, &AGrass::OnHit);

	RootComponent = rayCastCollision;

	grass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrassMesh"));

	grass->SetupAttachment(rayCastCollision);

	arrowcomponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	arrowcomponent->SetupAttachment(grass);

}

// Called when the game starts or when spawned
void AGrass::BeginPlay()
{
	Super::BeginPlay();

	// Select a mesh
	grass->SetStaticMesh(grassMeshses[FMath::RandRange(0, (grassMeshses.Num() - 1))]);

	grassColor = GetRandColor();

	dmiMat = UMaterialInstanceDynamic::Create(grassMat, this);
	grass->SetMaterial(0, dmiMat);
	// Use the bush material
	dmiMat->SetVectorParameterValue("SpawnpointColor", grassColor);

	arrowRotation = arrowcomponent->GetComponentRotation();	// World Space!
}

// Called every frame
void AGrass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrass::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AGrass::GrassBurst()
{
	UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(grassBurst, grass, NAME_None, FVector(0.f, 0.f, 0.f), arrowRotation, EAttachLocation::KeepRelativeOffset, true);
	if (particleComp) {
		particleComp->SetNiagaraVariableLinearColor(FString("ParticleColor"), grassColor);

		// Set a new random time
		int index = FMath::RandRange(0, (grassSounds.Num()) - 1);
		UGameplayStatics::PlaySoundAtLocation(this, grassSounds[index], GetActorLocation());
	}
}

void AGrass::ContainsFuzzy()
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

void AGrass::FuzzyPrepared()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGrass::PlaySound, FMath::RandRange(soundTimeMin, soundTimeMax), true);
}

void AGrass::PlaySound()
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
		GrassBurst();
		playing = false;
	}
}

FLinearColor AGrass::GetRandColor()
{
	float rMin = 0.f;
	float rMax = 0.036368f;
	float g = 0.078125f;
	float bMin = 0.006892f;
	float bMax = 0.01969f;

	FLinearColor tempColor = FLinearColor(FMath::RandRange(rMin, rMax), g, FMath::RandRange(bMin, bMax));
	return tempColor;
}
