// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#pragma once
#include "Interact_I.h"
#include "Bush.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API ABush : public AActor, public IInteract_I
{
	GENERATED_BODY()

	UPROPERTY()
	class UTextRenderComponent* textComponent;

	bool bTRActive = false;

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
	const int soundTimeMax = 6;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* rayCastCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* bush;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* arrowcomponent;

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

	FRotator arrowRotation;

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

	virtual void ActPressE(FVector start) override;

	virtual void LeavePoint() override;

};
