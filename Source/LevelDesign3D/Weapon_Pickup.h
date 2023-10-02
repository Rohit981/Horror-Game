// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "LevelDesign3DCharacter.h"
#include "Weapon_Pickup.generated.h"

/**
 * 
 */



UCLASS()
class LEVELDESIGN3D_API UWeapon_Pickup : public USphereComponent
{
	GENERATED_BODY()

public:

	UWeapon_Pickup();
protected:

	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
