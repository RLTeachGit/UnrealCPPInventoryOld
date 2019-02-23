// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EngineGlobals.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include <Runtime/Engine/Classes/Engine/Engine.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include "GameFramework/Actor.h" //Now needed as Unreal has gone to a minimal
#include "Runtime/Engine/Classes/Engine/EngineTypes.h" //Needed to set Mobility
#include "Components/ActorComponent.h"
#include "MovingPlatform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPPINVENTORY_API UMovingPlatform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovingPlatform();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    const char* cCategory = "Moving Platform"; //Where it shows in IDE

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    UFUNCTION(BlueprintCallable, Category = cCategory)
    void     SetMovable();
    
protected:
    UPROPERTY()
    AActor* Actor;
	
};
