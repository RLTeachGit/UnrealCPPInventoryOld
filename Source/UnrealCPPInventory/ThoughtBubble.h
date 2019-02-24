// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h" //For UWidget
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h" //For Text Render

#include "Runtime/Core/Public/Math/Color.h" //Needed for FColor
#include "GameFramework/Actor.h" //Now needed as Unreal has gone to a minimal include system

#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ThoughtBubble.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALCPPINVENTORY_API UThoughtBubble : public USceneComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UThoughtBubble(const FObjectInitializer& ObjectInitializer);
    virtual void PostInitProperties() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	const	char* CategoryName = "ThoughtBubble"; //This is there this will show in IDE

	//Undo parent scaling
	void	UndoTransform();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	UWidgetComponent* BubbleWidget;

	UPROPERTY()
	UTextRenderComponent* BubbleText;

	UFUNCTION(BlueprintCallable, Category = CategoryName) //Make this accesible from BP's
	void	SetText(FText Text);

	UFUNCTION(BlueprintPure, Category = CategoryName)
	FText	GetText();

	UFUNCTION(BlueprintCallable, Category = CategoryName)
	void	SetColour(FColor Colour);

};
