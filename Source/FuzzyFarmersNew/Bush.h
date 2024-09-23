// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bush.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API ABush : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABush();

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
	class UStaticMeshComponent* bush;

	UPROPERTY()
	FLinearColor leavesColor;

	class USoundWave* fuzzyHint;

	UPROPERTY(EditAnywhere)
	TArray<class USoundWave*> fuzzySounds;

	UPROPERTY(EditAnywhere)
	TArray<class USoundWave*> leavesSounds;

	UPROPERTY(EditAnywhere)
	TArray<class UStaticMesh*> bushMeshses;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* playerCollision;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* leavesBurst;

	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* bushMat;

	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	bool containsFuzzy = false;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void LeavesBurst();

	UFUNCTION()
	void ContainsFuzzy();

	UFUNCTION()
	void FuzzyPrepared();

	UFUNCTION()
	void PlaySound();

	UFUNCTION()
	FLinearColor GetRandColor();

};
