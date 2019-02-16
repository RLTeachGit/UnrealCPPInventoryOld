#include "BaseActor.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	//Set this actor to call Tick() every frame.
	//You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRotation(false); //Default is stopped
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Call base class
	if (isRotating)
	{
		FRotator tCurrentRotation = GetActorRotation(); //Get Current rotator
		tCurrentRotation.Yaw += DeltaTime * Speed; //Change rotation around Z
		SetActorRotation(tCurrentRotation); //Set to object
	}
}

void ABaseActor::SetRotation(bool Rotate) 
{
	isRotating = Rotate;
}

