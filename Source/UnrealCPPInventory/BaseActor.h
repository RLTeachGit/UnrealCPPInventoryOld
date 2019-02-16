#pragma once

#include "CoreMinimal.h"
#include <EngineGlobals.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include <Runtime/Engine/Classes/Engine/Engine.h> //Needed for GEngine->AddOnScreenDebugMessage()
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "BaseActor.generated.h"

UCLASS()
class UNREALCPPINVENTORY_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//This allows you to specify how theis variable can be interacted with
	//in Blueprints & IDE, its a MACRO, which adds the "hooks"
	//Unreal needs to do this
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Value")
	float Speed;

	//Show in IDE and BP but cant edit
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "User Value")
	bool isRotating;

	//Marks this function to be callable from a child blueprint
	UFUNCTION(BlueprintCallable, Category = "User Function")
	void SetRotation(bool Rotate);

};
