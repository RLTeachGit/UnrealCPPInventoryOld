// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EngineGlobals.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include <Runtime/Engine/Classes/Engine/Engine.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include "GameFramework/Actor.h" //Now needed as Unreal has gone to a minimal include system
#include "MyItem.h"
#include "Components/ActorComponent.h"
#include "MyInventory.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALCPPINVENTORY_API UMyInventory : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Added code
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddItem(UMyItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int	 GetWeights();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int	 GetCount();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory") //Expose Array of items in Blueprints
		TArray <UMyItem*> Items;

	AActor* GetActor();

protected: //Internal variables
	AActor* Actor;		//Get link to actor who owns us and cache

private:
	float InventoryTick = 1.0f;
	float InventoryDeltaTime = 0.0f;
};
