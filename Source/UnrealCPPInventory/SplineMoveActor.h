// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <EngineGlobals.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include <Runtime/Engine/Classes/Engine/Engine.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include "Runtime/Engine/Classes/Components/SplineComponent.h" //Needed for Spline
#include "Runtime/Engine/Classes/Curves/CurveFloat.h" //Needed for CurveFloat
#include "Runtime/Engine/Classes/Components/TimelineComponent.h" //Needed for FOnTimelineFloat
#include "SplineMoveActor.generated.h"

UCLASS()
class UNREALCPPINVENTORY_API ASplineMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineMoveActor(const FObjectInitializer& ObjectInitializer);
    
    //Called when item changed in Editor
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
private:

    UFUNCTION() //Need this or BindUFunction() wont bind
    void        TimelineTick(float Value); //Timeline callback

    FTimeline    Timeline; //TimeLine component

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Instanced, Category = CATEGORY) //Instanced will make a copy for each use
    class USplineComponent* PathSpline;

    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = CATEGORY)
    UCurveFloat* FloatTimeLine; //Can edit this in IDE

    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = CATEGORY)
    AActor* UpdateActor; //Can edit this in IDE

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY)
    bool Debug; //Draw Debug or not
    

};
