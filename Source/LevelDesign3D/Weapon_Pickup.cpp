// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Pickup.h"

UWeapon_Pickup::UWeapon_Pickup()
{
	SphereRadius = 32.f;
}

void UWeapon_Pickup::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UWeapon_Pickup::OnSphereBeginOverlap);
}

void UWeapon_Pickup::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ALevelDesign3DCharacter* Character = Cast<ALevelDesign3DCharacter>(OtherActor);
	if (Character != nullptr)
	{
		Character->has_Weapon_PickedUP = true;
		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
