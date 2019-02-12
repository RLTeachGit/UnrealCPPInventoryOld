// Fill out your copyright notice in the Description page of Project Settings.

#include "MyItem.h"


UMyItem::UMyItem() {
	UE_LOG(LogTemp, Display, TEXT("UMyItem() Called"));
}

UMyItem::UMyItem(const FObjectInitializer& ObjectInitializer) {
	UE_LOG(LogTemp, Display, TEXT("UMyItem(const FObjectInitializer& ObjectInitializer) called"));
}

//Default item has zero weight
int UMyItem::GetWeight_Implementation() {
	return	0;
}


void UMyItem::ItemTick_Implementation(float DeltaTime) {
	UE_LOG(LogTemp, Display, TEXT("Item Tick called %s %d"), *Actor->GetActorLabel(), GetWeight());
}


void	UMyItem::OnAdd_Implementation(UMyInventory* Inventory) {
	this->Inventory = Inventory;
	this->Actor = Inventory->GetActor();	//Set Actor
	UE_LOG(LogTemp, Display, TEXT("OnAdd called %s %d"), *Actor->GetActorLabel(), GetWeight());
}

