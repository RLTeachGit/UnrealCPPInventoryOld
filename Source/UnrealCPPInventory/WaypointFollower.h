// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h" //Now needed as Unreal has gone to a minimal
#include "WaypointFollower.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPPINVENTORY_API UWaypointFollower : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWaypointFollower();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: //User Properties

	UPROPERTY(EditAnywhere, Category = UserSettings)
	TArray<AActor*> Waypoints; //Make an array of Waypoints

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserSettings) //Show but dont allow edit
	int		CurrentIndex;		//We will start this at -1 to show its not initalised

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserSettings) //Allow IDE & BP edits
	float	Speed = 1;		//Sets the speed of movement

public: //External functions

	UFUNCTION(BlueprintCallable, Category = UserSettings)
	void	Reset();

	UFUNCTION(BlueprintCallable, Category = UserSettings)
	void	SetMoving(bool Move=true);
		
private:

	void	UpdateActorLocation(float DeltaTime);

	float	CurrentLERP; //LERP Amount 0-1

	bool	isMoving; //Only move if set

};
