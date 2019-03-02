// Fill out your copyright notice in the Description page of Project Settings.

#include "WaypointFollower.h"


// Sets default values for this component's properties
UWaypointFollower::UWaypointFollower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWaypointFollower::BeginPlay()
{
	Super::BeginPlay();
	Reset();
}


// Called every frame
void UWaypointFollower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateActorLocation(DeltaTime);
}

void UWaypointFollower::Reset() 
{
	CurrentIndex = 0;
	CurrentLERP = 0;
	isMoving = false;

	UpdateActorLocation(0);
}

void UWaypointFollower::UpdateActorLocation(float DeltaTime)
{

	AActor* tOwningActor = GetOwner(); //Find actor who owns this component
	if (IsValid(tOwningActor)) //Make sure its valid NB:Needs #include "GameFramework/Actor.h" to work
	{
		int tWayPointCount = Waypoints.Num();
		if (tWayPointCount == 0) return; //No waypoint nothing to do
		if (tWayPointCount == 1) //Only one Waypoint, so go there
		{
			if(!IsValid(Waypoints[0])) return;	//Array entry blank
			tOwningActor->SetActorLocation(Waypoints[0]->GetActorLocation()); //Just use first WP
			return; //Done
		}

		//LERP calculates a point on the line between 2 position vector
		//Alpha is a normalised variable 0 is Point A 1 is Point B
		//Between 0-1 its a proportion between

		AActor* tFromActor = Waypoints[CurrentIndex];
		AActor* tToActor = Waypoints[(CurrentIndex + 1) % tWayPointCount];

		if ((!IsValid(tFromActor) || !IsValid(tToActor))) return; //One or both Array entries blank

		FVector tFrom = tFromActor->GetActorLocation(); //Get Current From WP
		FVector tTo = tToActor->GetActorLocation(); //To WP is next one , but needs to loop, so use Modulo

		FVector tNewLocation = FMath::Lerp(tFrom, tTo, CurrentLERP);
		tOwningActor->SetActorLocation(tNewLocation);

		if (!isMoving)	return; //Don't update time if not set to moving, keeps it still

		CurrentLERP += DeltaTime * Speed;
		if (CurrentLERP > 1)
		{
			while(CurrentLERP>1) CurrentLERP -= 1; //Loop LERP alpha (like floating Modulus)
			CurrentIndex = (CurrentIndex + 1) % tWayPointCount; //Next Way point , loop if at the end
		}
	}
}


void	UWaypointFollower::SetMoving(bool Move)
{
	isMoving = Move; //Allow movement
}




