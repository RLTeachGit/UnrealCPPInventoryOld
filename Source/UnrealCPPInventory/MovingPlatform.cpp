// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


// Sets default values for this component's properties
UMovingPlatform::UMovingPlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    Actor = GetOwner(); //Get Owning Actor
    SetMovable();
}

void     UMovingPlatform::SetMovable()
{
    if(IsValid(Actor))  //Make sure Actor is set
    {
        if(!Actor->IsRootComponentMovable()) //May already be moveable
        {
            USceneComponent* tRoot = Actor->GetRootComponent();
            UE_LOG(LogTemp, Warning, TEXT("Making %s Movable"),*Actor->GetName());
            tRoot->SetMobility(EComponentMobility::Movable); //Allow it to move
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Actor missing"));
    }
}


// Called when the game starts
void UMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMovingPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

