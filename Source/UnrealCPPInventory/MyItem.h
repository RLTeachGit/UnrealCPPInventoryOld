// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UMyInventory;
class UMyItem; //Forward reference


#include "MyInventory.h"
#include "GameFramework/Actor.h" //Now needed as Unreal has gone to a minimal include system
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Core/Public/Internationalization/Text.h" //Needed for FText
#include "Runtime/Core/Public/Containers/UnrealString.h" //Needed for FString
#include "MyItem.generated.h"


/**
 *
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALCPPINVENTORY_API UMyItem : public UObject {
	GENERATED_BODY()

    UMyItem(); //Simple constructor
	UMyItem(const FObjectInitializer& ObjectInitializer); //Complex constuctor

	//Added code
public:
    
    //Get Item own reported Weight
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure) //Event can be overriden in BP but also called. It does not affect item
    int	GetWeight();	//Can be overidded in BP
	virtual int GetWeight_Implementation(); //This is the baseclass implementation

    //Called when Item ticks default each second
	UFUNCTION(BlueprintNativeEvent)
    void	ItemTick(float DeltaTime);	//Can be overidded in BP
	virtual void ItemTick_Implementation(float DeltaTime); //This is the baseclass implementation

    //Called when Item is added to Inventory
	UFUNCTION(BlueprintNativeEvent) //Event is can be overriden
    void	OnAdd(UMyInventory* Inventory); //Can override in BP
	virtual void	OnAdd_Implementation(UMyInventory* Inventory); //C++ parent

    //Called when Item is removed from Inventory
    UFUNCTION(BlueprintNativeEvent)
    void    OnRemove(); //Can override in BP
    virtual void    OnRemove_Implementation(); //C++ parent
    
    //Called to get Items reported Name
    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable)
    FString    GetItemName(); //Can override this in BP
    virtual FString    GetItemName_Implementation(); //C++ parent implementation

	//Called to get Item as text
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable)
	FString    ToString(); //Can override this in BP
	virtual FString    ToString_Implementation(); //C++ parent implementation

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserSetting) //Expose Actor variable in Blueprints
    AActor* OwningActor; //Pointer to actor who owns this item
    
	UMyInventory* OwningInventory; //Pointer to Link back to Inventory who owns this item
};
