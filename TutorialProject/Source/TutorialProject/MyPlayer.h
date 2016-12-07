// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class TUTORIALPROJECT_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

	/* INPUTS */
	void MoveForward(float value);
	void MoveRight(float value);
	void LookYaw(float value);
	void LookPitch(float value);
	void Use();

	class AInteractableActor* FindFocusedActor();

	void HandleHighlight();

	/* Overrides */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float InteractionDistance = 300.f;
	
	AInteractableActor* FocusedActor;

	FCollisionQueryParams TraceParams;
};
