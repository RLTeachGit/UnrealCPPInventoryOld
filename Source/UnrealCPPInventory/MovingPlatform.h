// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EngineGlobals.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include <Runtime/Engine/Classes/Engine/Engine.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include "GameFramework/Actor.h" //Now needed as Unreal has gone to a minimal
#include "Runtime/Engine/Classes/Engine/EngineTypes.h" //Needed to set Mobility

#include "Runtime/Engine/Classes/Curves/CurveFloat.h" //Needed for CurveFloat
#include "Runtime/Engine/Classes/Components/TimelineComponent.h" //Needed for FOnTimelineFloat
#include "Components/ActorComponent.h"
#include "MovingPlatform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPPINVENTORY_API UMovingPlatform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovingPlatform(const FObjectInitializer& ObjectInitializer); //Use Expanded version of constructor, which passes ObjectInitializer

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    const char* cCategory = "Moving Platform"; //Where it shows in IDE

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	FTimeline	Timeline;

	FVector		StartLocation;

	FVector		EndLocation;

	FOnTimelineFloat ProgressFunction;	//Callback for timeline

	UFUNCTION()
	void		TimelineTick(float Value);

public:
    UFUNCTION(BlueprintCallable, Category = cCategory) //We can call this from the Blueprint
    void     SetMovable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = cCategory)
	float Height;

	UPROPERTY(EditAnywhere, Category = cCategory)
	UCurveFloat* FloatTimeLine;

};
