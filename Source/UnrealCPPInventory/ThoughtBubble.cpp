// Fill out your copyright notice in the Description page of Project Settings.

#include "ThoughtBubble.h"


// Sets default values for this component's properties
UThoughtBubble::UThoughtBubble()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    BubbleWidget = CreateDefaultSubobject<UWidgetComponent>("Widget");
    if(IsValid(BubbleWidget))
    {
        UE_LOG(LogTemp, Display, TEXT("Bubble Widget Initialised"));
        BubbleWidget->SetWidgetSpace(EWidgetSpace::World);
        BubbleWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
        //BubbleWidget->SetDrawSize(FVector2D(100.0f, 20.0f));
        BubbleWidget->SetVisibility(true);
        BubbleWidget->RegisterComponent();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Bubble Widget failed"));
    }
}


// Called when the game starts
void UThoughtBubble::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UThoughtBubble::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

