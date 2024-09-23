// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestNiagaraSpaner.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API ATestNiagaraSpaner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestNiagaraSpaner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	void DirtBurst();

	UFUNCTION()
	void ContainsFuzzy();

	UFUNCTION()
	void FuzzyPrepared();

	UFUNCTION()
	void PlaySound();

};
