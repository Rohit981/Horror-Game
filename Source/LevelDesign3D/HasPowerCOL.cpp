// Fill out your copyright notice in the Description page of Project Settings.


#include "HasPowerCOL.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHasPowerCOL::AHasPowerCOL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AHasPowerCOL::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHasPowerCOL::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ALevelDesign3DCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
}


// Called every frame
void AHasPowerCOL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHasPowerCOL::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Character != nullptr && Character->has_Power == true)
	{		
		spawnEnemy = true;

		// Unregister from the Overlap Event so it is no longer triggered
		OverlapBox->OnComponentBeginOverlap.RemoveAll(this);
	}
}
