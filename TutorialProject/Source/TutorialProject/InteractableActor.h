// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TutorialProject.h"
#include "InteractableActor.generated.h"

UCLASS()
class TUTORIALPROJECT_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(AActor* Caller);

	virtual void OnInteract_Implementation(AActor* Caller);

	void OnBeginFocus();
	void OnEndFocus();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	UPROPERTY(EditDefaultsOnly)
	uint32 bCanInteract : 1;
	TArray<class UMeshComponent*> Meshes;
	UPROPERTY(EditDefaultsOnly)
	EStencilColour Colour = EStencilColour::SC_Blue;
};
