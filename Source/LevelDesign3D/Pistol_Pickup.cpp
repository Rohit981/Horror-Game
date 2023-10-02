// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol_Pickup.h"
#include "Components/SphereComponent.h"

// Sets default values
APistol_Pickup::APistol_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Box"));
	OverlapSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OverlapSphere->SetGenerateOverlapEvents(true);
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &APistol_Pickup::OnSphereBeginOverlap);

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Gun->AttachToComponent(OverlapSphere, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void APistol_Pickup::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void APistol_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APistol_Pickup::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ALevelDesign3DCharacter* Character = Cast<ALevelDesign3DCharacter>(OtherActor);
	if (Character != nullptr)
	{
		Character->has_Weapon_PickedUP = true;

		Gun->SetVisibility(false);
		// Unregister from the Overlap Event so it is no longer triggered
		OverlapSphere->OnComponentBeginOverlap.RemoveAll(this);
	}
}

