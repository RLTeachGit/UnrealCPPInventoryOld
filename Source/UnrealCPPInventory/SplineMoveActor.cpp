// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoveActor.h"

#include "DrawDebugHelpers.h"

// Sets default values
ASplineMoveActor::ASplineMoveActor(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PathSpline = ObjectInitializer.CreateDefaultSubobject<USplineComponent>(this, TEXT("Spline"));
    PathSpline->SetupAttachment(RootComponent);
    PathSpline->bEditableWhenInherited = true;
    Debug = false;

}

// Called when the game starts or when spawned
void ASplineMoveActor::BeginPlay()
{
	Super::BeginPlay();
    if (IsValid(FloatTimeLine)) {
        FOnTimelineFloat tProgressFunction;    //Callback Wrapper for timeline
        
        tProgressFunction.BindUFunction(this, FName("TimelineTick")); //Set tick function (as text) to call
        
        Timeline.AddInterpFloat(FloatTimeLine, tProgressFunction); //Link to Timeline tick
        Timeline.SetLooping(true); //Loop TimeLine
        
        Timeline.PlayFromStart(); //reset to start
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s Requires a FloatTimeLine"),*GetName()));
    }
}

// Called every frame
void ASplineMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Mahe sure parent ticks
    if (FloatTimeLine)
    {
        Timeline.TickTimeline(DeltaTime);
    }
}

void        ASplineMoveActor::TimelineTick(float Value) //Timeline callback
{
    float tLength = PathSpline->GetSplineLength(); //Lenght of whole spline
    
    FVector tNewLocation = PathSpline->GetLocationAtDistanceAlongSpline(Value * tLength, ESplineCoordinateSpace::World);
    
    FRotator tNewRotator = PathSpline->GetRotationAtDistanceAlongSpline(Value * tLength, ESplineCoordinateSpace::World);
    
    tNewRotator.Pitch = 0;

    if(Debug)   DrawDebugSphere(GetWorld(), tNewLocation, 5, 8, FColor(181,0,0), true, -1, 0, 2);
    
    if(IsValid(UpdateActor))
    {
        UpdateActor->SetActorLocation(tNewLocation);
        UpdateActor->SetActorRotation(tNewRotator);
    }
}


/* If MyBool belongs to the ASomeActor */
void ASplineMoveActor::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
    Super::PostEditChangeProperty(e);
    
    FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
    if (PropertyName == GET_MEMBER_NAME_CHECKED(ASplineMoveActor, UpdateActor)) {
        if(IsValid(UpdateActor))
        {
            TimelineTick(0); //Set to start position
        }
    }
}

