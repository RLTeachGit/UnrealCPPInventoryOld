// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UMyInventory; //Forward reference
class UMyItem;

#include "MyInventory.h"
#include "GameFramework/Actor.h" //Now needed as Unreal has gone to a minimal include system
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyItem.generated.h"

/**
 *
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALCPPINVENTORY_API UMyItem : public UObject {
	GENERATED_BODY()

		UMyItem();
	UMyItem(const FObjectInitializer& ObjectInitializer);

	//Added code
public:
	UFUNCTION(BlueprintNativeEvent)
		int	GetWeight();	//Can be overidded in BP
	virtual int GetWeight_Implementation(); //This is the baseclass implementation


	UFUNCTION(BlueprintNativeEvent)
		void	ItemTick(float DeltaTime);	//Can be overidded in BP
	virtual void ItemTick_Implementation(float DeltaTime); //This is the baseclass implementation


	UFUNCTION(BlueprintNativeEvent)
		void	OnAdd(UMyInventory* Inventory); //Can override in BP
	virtual void	OnAdd_Implementation(UMyInventory* Inventory); //C++ parent 

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory") //Expose Actor variable in Blueprints
		AActor* Actor;
	UMyInventory* Inventory;




};
