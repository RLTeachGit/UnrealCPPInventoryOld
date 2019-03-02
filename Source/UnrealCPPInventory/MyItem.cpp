// Fill out your copyright notice in the Description page of Project Settings.

#include "MyItem.h"


UMyItem::UMyItem()
{
	UE_LOG(LogTemp, Display, TEXT("UMyItem() Called"));
}

UMyItem::UMyItem(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Display, TEXT("UMyItem(const FObjectInitializer& ObjectInitializer) called"));
}

//Default item has zero weight
int UMyItem::GetWeight_Implementation()
{
	return	0;
}

//Parent implementation of Tick
void UMyItem::ItemTick_Implementation(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("Item Tick called %s %d"), *OwningActor->GetActorLabel(), GetWeight());
}


//Parent implementation of OnRemove
void    UMyItem::OnRemove_Implementation()
{
    UE_LOG(LogTemp, Display, TEXT("OnRemove called %s %d"), *OwningActor->GetActorLabel(), GetWeight());
    OwningInventory = nullptr;
    OwningActor = nullptr;    //Clear references
}

//Parent implementation of OnAdd
void	UMyItem::OnAdd_Implementation(UMyInventory* Inventory)
{
	OwningInventory = Inventory;
	OwningActor = OwningInventory->GetActor();	//Set Actor
	UE_LOG(LogTemp, Display, TEXT("OnAdd called %s %d"), *OwningActor->GetActorLabel(), GetWeight());
}


FString    UMyItem::GetName_Implementation() //C++ parent implementation
{
    return FString("Default Item");
}

