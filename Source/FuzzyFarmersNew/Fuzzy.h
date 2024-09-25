// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Fuzzy.generated.h"

UCLASS()
class FUZZYFARMERSNEW_API AFuzzy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFuzzy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* captureCollision;

	UPROPERTY()
	class USkeletalMeshComponent* fuzzyMesh;

	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* fuzzyMat;

	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* currentDirection;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* nextDirection;

	UFUNCTION()
	void LaunchTowardsPlayer();

private:
	float speed;
	int pointValue;
	FLinearColor fuzzyColor = FLinearColor(0.604167f, 0.f, 0.116147f, 1.f);

};
