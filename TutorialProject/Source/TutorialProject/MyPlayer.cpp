// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialProject.h"
#include "MyPlayer.h"
#include "InteractableActor.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TraceParams = FCollisionQueryParams(FName(TEXT("TraceParams")), false, this);
	TraceParams.bTraceComplex = false;
	TraceParams.bTraceAsyncScene = false;
	TraceParams.bReturnPhysicalMaterial = false;
}


// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (Controller && Controller->IsLocalController())
	{
		HandleHighlight();
	}
	
}

// Called every frame
void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &AMyPlayer::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &AMyPlayer::LookPitch);
	InputComponent->BindAction("Use", IE_Pressed, this, &AMyPlayer::Use);

}

void AMyPlayer::MoveForward(float value)
{
	FRotator Rotation(0, GetActorRotation().Yaw, 0);
	FVector Forward = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Forward, value);
}

void AMyPlayer::MoveRight(float value)
{
	FRotator Rotation(0, GetActorRotation().Yaw, 0);
	FVector Right = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(Right, value);
}

void AMyPlayer::LookYaw(float value)
{
	AddControllerYawInput(value);
}

void AMyPlayer::LookPitch(float value)
{
	AddControllerPitchInput(value);
}

void AMyPlayer::Use()
{
	AInteractableActor* Interactable = FindFocusedActor();
	if (Interactable)
	{
		Interactable->OnInteract(this);
	}
}

AInteractableActor* AMyPlayer::FindFocusedActor()
{
	if (!Controller) { return nullptr; }
	FVector Location;
	FRotator Rotation;
	FHitResult Hit(ForceInit);
	Controller->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * InteractionDistance);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);
	if (Hit.bBlockingHit)
	{
		AInteractableActor* MyCastActor = Cast<AInteractableActor>(Hit.GetActor());
		if (MyCastActor) { return MyCastActor; }
	}
	return nullptr;
}

void AMyPlayer::HandleHighlight()
{
	AInteractableActor* NewHighlight = FindFocusedActor();
	if (NewHighlight)
	{
		if (NewHighlight != FocusedActor)
		{
			if (FocusedActor)
			{
				FocusedActor->OnEndFocus();
				NewHighlight->OnBeginFocus();
				FocusedActor = NewHighlight;
			}

		}

	}
	else
	{
		if(FocusedActor)
		{
			FocusedActor->OnEndFocus();
			FocusedActor = nullptr;
		}
	}
}