// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grass.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API AGrass : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool playing = false;

	FTimerHandle TimerHandle;

	int randTimeInterval;
	const int soundTimeMin = 3;
	const int soundTimeMax = 8;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* rayCastCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* grass;

	UPROPERTY()
	FLinearColor grassColor;

	UPROPERTY(EditAnywhere)
	TArray<class USoundWave*> fuzzySounds;

	UPROPERTY(EditAnywhere)
	TArray<class USoundWave*> grassSounds;

	UPROPERTY(EditAnywhere)
	TArray<class UStaticMesh*> grassMeshses;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* grassBurst;

	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* grassMat;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* dmiMat;

	bool containsFuzzy = false;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void GrassBurst();

	UFUNCTION()
	void ContainsFuzzy();

	UFUNCTION()
	void FuzzyPrepared();

	UFUNCTION()
	void PlaySound();

	UFUNCTION()
	FLinearColor GetRandColor();

};
