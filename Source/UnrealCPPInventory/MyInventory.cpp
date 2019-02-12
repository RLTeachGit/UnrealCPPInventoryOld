// Fill out your copyright notice in the Description page of Project Settings.



#include "MyInventory.h"

// Sets default values for this component's properties
UMyInventory::UMyInventory() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMyInventory::BeginPlay() {
	Super::BeginPlay();
	Actor = GetOwner(); //Cache Actor Owner of this Component, should not change unless removed
	if (Actor != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("I am owned by %s"), *Actor->GetActorLabel()));
	}
}


// Called every frame
void UMyInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	InventoryDeltaTime += DeltaTime;
	if (InventoryDeltaTime >= InventoryTick) {
		for (auto tItem : Items) {	//Go through the array
			tItem->ItemTick(InventoryDeltaTime); //Tick each item 
		}
		InventoryDeltaTime = 0.0f;
	}
}

bool UMyInventory::AddItem(UMyItem * Item) {
	if (Item != nullptr) {
		Items.Add(Item); //Add item to Item array
		Item->OnAdd(this); //Give item a link back to the owning actor
		return	true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Invalid null Item for %s"), *Actor->GetActorLabel()));
	return false;	//No successful
}

//Get Item Count from Array
int	 UMyInventory::GetCount() {
	return	Items.Num();	//Return Object count
}

//Get combined weight of items
int	 UMyInventory::GetWeights() {
	int	tWeight = 0;
	for (auto tItem : Items) {	//Go through the array
		tWeight += tItem->GetWeight(); //Add up the weights
	}
	return tWeight;
}


AActor* UMyInventory::GetActor() {
	return Actor;
}