// Fill out your copyright notice in the Description page of Project Settings.

#include "ThoughtBubble.h"

#include <EngineGlobals.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include <Runtime/Engine/Classes/Engine/Engine.h> //Needed for GEngine->AddOnScreenDebugMessage()

// Sets default values for this component's properties
UThoughtBubble::UThoughtBubble(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    BubbleWidget = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this,TEXT("Widget")); //Make a Widget for Text to go on (like Unity Canvas)
	if (IsValid(BubbleWidget)) //Could fail
	{
		BubbleText = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(BubbleWidget, TEXT("Text")); //The owner must be the canvas or this crashes
		if (IsValid(BubbleText)) //Could Fail
		{
			BubbleWidget->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform); //Set Parent to whom we are attached to
			BubbleWidget->SetWidgetSpace(EWidgetSpace::World); //World space Widget
			BubbleWidget->SetDrawSize(FVector2D(100.0f, 20.0f)); //Size of Widget
			BubbleWidget->SetVisibility(true); //Show it

			BubbleText->AttachToComponent(BubbleWidget, FAttachmentTransformRules::KeepRelativeTransform); //Make Text a child of UIWidget
			BubbleText->SetVisibility(true);
            BubbleText->SetText(FText::FromString("Tought")); //Set Inital text
			BubbleText->SetVerticalAlignment(EVRTA_TextCenter);	//Center
			BubbleText->SetHorizontalAlignment(EHTA_Center);


			return; //All is well
		}
	}
    UE_LOG(LogTemp, Error, TEXT("Bubble Widget failed")); //Error
}

//Called when most other things have been set up, such as the Actor we are linked to
void UThoughtBubble::PostInitProperties()
{
    Super::PostInitProperties(); //Must call parent version or Kaboom
    UndoTransform();
}

//Undo Parent transform so Text does not get squished
void	UThoughtBubble::UndoTransform()
{
	AActor* tParentActor = GetAttachmentRootActor(); //Get parent
	if (IsValid(tParentActor) && IsValid(BubbleWidget))
	{
		BubbleWidget->SetWorldScale3D(FVector::OneVector); //Unscale from parent transform
		BubbleWidget->SetWorldLocation(tParentActor->GetActorLocation() + GetRelativeTransform().GetLocation()); //Recalculate offset to undo Parent Scale
	}
}

// Called when the game starts
void UThoughtBubble::BeginPlay()
{
	Super::BeginPlay();
	UndoTransform();
}


// Called every frame
void UThoughtBubble::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UndoTransform();
}

//BP compatible set text routine
void UThoughtBubble::SetText(FText Text) 
{
	BubbleText->SetText(Text);
}

//BP compatible get text routine
FText UThoughtBubble::GetText() 
{
	return BubbleText->Text;
}
//BP compatible set text colour routine
void	UThoughtBubble::SetColour(FColor Colour)
{
	BubbleText->SetTextRenderColor(Colour);
}

