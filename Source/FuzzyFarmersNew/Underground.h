// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Underground.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API AUnderground : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUnderground();

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
	class UStaticMeshComponent* dirtMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor dirtMeshColor;

	UPROPERTY(EditAnywhere)
	TArray<class USoundWave*> fuzzySounds;

	UPROPERTY(EditAnywhere)
	TArray<class USoundWave*> dirtSounds;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* dirtParticle;

	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* dirtMat;

	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	bool containsFuzzy = false;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void DirtBurst();

	UFUNCTION()
	void ContainsFuzzy();

	UFUNCTION()
	void FuzzyPrepared();

	UFUNCTION()
	void PlaySound();

};
