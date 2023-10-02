// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "BlendViewTarget.h"
#include "EnemySpawnCOL.generated.h"

class UBoxComponent;

UCLASS()
class LEVELDESIGN3D_API AEnemySpawnCOL : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnCOL();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
		TSubclassOf<class AEnemy> ChaseEnemy;

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
		ABlendViewTarget* SpawnEnemyCollider;

	int spawnCount = 0;

	AEnemy* Enemy;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
