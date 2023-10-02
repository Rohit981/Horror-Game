// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelDesign3DCharacter.h"
#include "HasPowerCOL.generated.h"

class UBoxComponent;

UCLASS()
class LEVELDESIGN3D_API AHasPowerCOL : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHasPowerCOL();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverlapBox;

	ALevelDesign3DCharacter* Character;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool spawnEnemy = false;

};
