// Fill out your copyright notice in the Description page of Project Settings.

#include "ForceJump.h"

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UForceJump::UForceJump()
{
	PrimaryComponentTick.bCanEverTick = true; //Allow tick
	OnSwitch();
}


// Called when the game starts
void UForceJump::BeginPlay()
{
	Super::BeginPlay();
	AActor* tOwningActor = GetOwner();
	if (IsValid(tOwningActor))
	{
		tOwningActor->OnActorBeginOverlap.AddDynamic(this, &UForceJump::OnOverlap); //Link Overlap action handler to our code
	}
}


// Called every frame
void UForceJump::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


//Will be called when box is overlapped
void UForceJump::OnOverlap(AActor * MyActor, AActor * OtherActor)
{
	if (!IsOn) return;

	ACharacter* tCharacter = Cast<ACharacter>(OtherActor); //Make sure we are character, will return null if not
	if (IsValid(tCharacter))
	{
		tCharacter->LaunchCharacter(FVector::UpVector * Force, false, false);
		Activated();
	}
}

void UForceJump::OnSwitch(bool State)
{
	IsOn = State;
}

void UForceJump::Activated_Implementation()
{
	
}
