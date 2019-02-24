// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


// Sets default values for this component's properties
UMovingPlatform::UMovingPlatform(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UMovingPlatform::PostInitProperties()
{
    Super::PostInitProperties(); //Make sure parent version called too
    Actor = GetOwner(); //Get Owning Actor & cache
    if(IsValid(Actor))
    {
        if(!Actor->IsRootComponentMovable()) //Check its moveable
        {
            if(IsValid(GEngine))
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s must be set to Moveable"),*Actor->GetName()));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning,TEXT("PostInitProperties:No Actor Yet"));
    }
}

// Called when the game starts
void UMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(Actor))  //Make sure Actor is set
	{
		if (IsValid(FloatTimeLine)) {
            FOnTimelineFloat tProgressFunction;    //Callback Wrapper for timeline

			tProgressFunction.BindUFunction(this, FName("TimelineTick")); //Set tick function (as text) to call

			Timeline.AddInterpFloat(FloatTimeLine, tProgressFunction); //Link to Timeline tick
			Timeline.SetLooping(true); //Loop TimeLine

			StartLocation = EndLocation = Actor->GetActorLocation(); //Initial position
			EndLocation.Z += Height; //Add Height

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
	if (IsValid(Actor) && Actor->IsRootComponentMovable())  //Make sure Actor is set & can move
	{
		FVector tNewPosition = FMath::Lerp(StartLocation, EndLocation, Value); //Will take Position from Start to End
		Actor->SetActorLocation(tNewPosition); //Reposition Actor
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

