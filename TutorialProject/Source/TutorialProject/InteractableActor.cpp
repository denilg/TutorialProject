// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialProject.h"
#include "InteractableActor.h"
#include "MyPlayer.h"


// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	for (UActorComponent* Mesh: GetComponentsByClass(UMeshComponent::StaticClass()))
	{
		UMeshComponent* thisMesh = Cast<UMeshComponent>(Mesh);
		if (thisMesh)
		{
			Meshes.Push(thisMesh);
			thisMesh->SetCustomDepthStencilValue((uint8)Colour);
		}
	}
	
}

// Called every frame
void AInteractableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractableActor::OnInteract_Implementation(AActor* Caller)
{
	AMyPlayer* Player = Cast<AMyPlayer>(Caller);
	if(Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Now Interacting"))
		Destroy();
	}
}

void AInteractableActor::OnBeginFocus()
{
	if (bCanInteract)
	{
		for (UMeshComponent* Mesh : Meshes)
		{
			Mesh->SetRenderCustomDepth(true);
		}
	}
}

void AInteractableActor::OnEndFocus()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}