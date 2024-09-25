// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputClasses.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputConfigData.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(inputMapping, 0);
		}
	}

	actor = GetComponentByClass(UCameraComponent::StaticClass());
	if (actor)
	{
		cameraComponent = Cast<UCameraComponent>(actor);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractLineTrace();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		input->BindAction(InputActions->Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		input->BindAction(InputActions->Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	if (Controller != nullptr)
	{
		FVector2D MovementVector = value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// add movement 
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = value.Get<FVector2D>();

		if (LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X);
		}

		if (LookValue.Y != 0.f)
		{
			float tmp = LookValue.Y * -1;
			AddControllerPitchInput(tmp);
		}
	}
}

void APlayerCharacter::InteractLineTrace()
{
	FHitResult OutHit;
	FVector start = cameraComponent->GetComponentLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector End = ((forwardVector * 1000) + start);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	
	if (GetWorld()->LineTraceSingleByChannel(OutHit, start, End, ECC_WorldDynamic, CollisionParams))
	{
		DrawDebugLine(GetWorld(), start, OutHit.ImpactPoint, FColor::Red, false, 2.0f, 0, 2.0f);

		hitActor = OutHit.GetActor();
		if (hitActor->Implements<UInteract_I>())
		{	
			IInteract_I* interface = Cast<IInteract_I>(hitActor);
			interface->ActPressE(start);
		}
	}
}


