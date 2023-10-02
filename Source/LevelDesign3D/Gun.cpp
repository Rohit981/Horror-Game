// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = GunAmmo;

	Gun_UI_Magazine = GunAmmo;
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AGun::Shoot(UCameraComponent* FollowCamera, AActor* Player, bool IsAds)
{
	float BulletSpreadRange = FMath::RandRange(BulletSpread * -1.f, BulletSpread);

	Start = FollowCamera->GetComponentLocation() + LineTraceOffset;
	End = ((FollowCamera->GetForwardVector() * 5000) + Start) + FVector(BulletSpreadRange, BulletSpreadRange, BulletSpreadRange);


	TArray<FHitResult> OutHit;

	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(FollowCamera->GetOwner());
	ActorsToIgnore.Add(Player);

	bool IsHit = false;

	IsHit = UKismetSystemLibrary::LineTraceMulti(Player->GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera),
		false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true, FLinearColor::Red, FLinearColor::Green, 0.f);


	/* UKismetSystemLibrary::LineTraceSingle(Player->GetWorld(), MuzzleComp->GetComponentLocation(), OutHit.ImpactPoint, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera),
		false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true, FLinearColor::Green, FLinearColor::Green, 1.f);*/


	if (IsHit == true)
	{
		for (int i = 0; i < OutHit.Num(); i++)
		{
			AEnemy* Enemy = Cast<AEnemy>(OutHit[i].GetActor());

			if (Enemy != nullptr)
			{
				Enemy->Enemy_Health -= 20;

				Enemy->DamageTaken(20);
			}



		}

	}

	
}

