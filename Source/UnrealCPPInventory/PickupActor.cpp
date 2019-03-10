// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupActor.h"

#include "InventoryComponent.h"

#include <EngineGlobals.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include <Runtime/Engine/Classes/Engine/Engine.h> //Needed for GEngine->AddOnScreenDebugMessage()

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}




// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &APickupActor::OnOverlap); //Link Overlap action handler to our code
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


//Function called when Actor overlaps this object
void APickupActor::OnOverlap(AActor * MyActor, AActor * OtherActor)
{
	TArray<UInventoryComponent*> tInventoryArray; //Array for Inventory components found should be just one
	OtherActor->GetComponents<UInventoryComponent>(tInventoryArray); //Get Inventory attached to Actor
	int tCount = tInventoryArray.Num(); //How many found?
	if (tCount == 0) //Just expecting one Inventory
	{
		if (IsValid(GEngine))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s does not have an Inventory Component"), *OtherActor->GetName()));
		}
	}
	else if (tCount > 1) //More than one
	{
		if (IsValid(GEngine))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s has multiple(%d) Inventory Components"), *OtherActor->GetName(), tCount));
		}
	}
	else //Correct number ie 1
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s add %s to Inventory"), *OtherActor->GetName(), *MyActor->GetName()));
		tInventoryArray[0]->AddItem(this);
	}
}


