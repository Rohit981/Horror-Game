// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnCOL.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemySpawnCOL::AEnemySpawnCOL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

}

// Called when the game starts or when spawned
void AEnemySpawnCOL::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawnCOL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnEnemyCollider->Is_Overlapped == true)
	{
		if (ChaseEnemy != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr && spawnCount == 0)
			{
				FVector Location = GetActorLocation();
				FRotator Rotation = GetActorRotation();

				Enemy = World->SpawnActor<AEnemy>(ChaseEnemy, Location, Rotation);

				

				spawnCount = 1;

				
				
			}
		}
	}

}

