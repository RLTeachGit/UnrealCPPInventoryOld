// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ForceJump.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPPINVENTORY_API UForceJump : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UForceJump();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Function called on Overlap
	UFUNCTION()
	void OnOverlap(AActor * MyActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnSwitch(bool State = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = User)
	float	Force = 1000.0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void    Activated(); //Can override this in BP
	virtual void    Activated_Implementation(); //C++ parent implementation



private:
	bool	IsOn;

};
