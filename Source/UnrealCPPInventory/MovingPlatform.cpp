// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


// Sets default values for this component's properties
UMovingPlatform::UMovingPlatform(const FObjectInitializer& ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

//Make the root object moveable, or we wont be able to move it
void     UMovingPlatform::SetMovable()
{
	AActor* tActor = GetOwner(); //Get Owning Actor & cache
	if(IsValid(tActor))  //Make sure Actor is set
    {
        if(!tActor->IsRootComponentMovable()) //May already be moveable
        {
            USceneComponent* tRoot = tActor->GetRootComponent(); //Make sure root is movable
            UE_LOG(LogTemp, Warning, TEXT("Making %s Movable"),*tActor->GetName());
            tRoot->SetMobility(EComponentMobility::Movable); //Allow it to move
        }
    }
}

// Called when the game starts
void UMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SetMovable();
	AActor* tActor = GetOwner(); //Get Owning Actor & cache
	if (IsValid(tActor))  //Make sure Actor is set
	{
		if (FloatTimeLine) {

			ProgressFunction.BindUFunction(this, FName("TimelineTick")); //Set tick function (as text) to call

			Timeline.AddInterpFloat(FloatTimeLine, ProgressFunction); //Link to Timeline tick
			Timeline.SetLooping(true);

			StartLocation = EndLocation = tActor->GetActorLocation();
			EndLocation.Z += Height;

			Timeline.PlayFromStart(); //reset to start
		}
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Actor missing"));
	}
}


void UMovingPlatform::TimelineTick(float Value) 
{
	AActor* tActor = GetOwner(); //Get Owning Actor & cache
	if (IsValid(tActor))  //Make sure Actor is set
	{
		FVector tNewPosition = FMath::Lerp(StartLocation, EndLocation, Value);
		tActor->SetActorLocation(tNewPosition);
	}
}

// Called every frame
void UMovingPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FloatTimeLine) {
		Timeline.TickTimeline(DeltaTime);
	}
}

