// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	
	
}



// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimInstance = GetMesh()->GetAnimInstance();

	if (Enemy_Health <= 0)
	{
		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	}

}

void AEnemy::DamageTaken(int BulletDMG)
{
	EnemyDamageTaken = BulletDMG;

	AnimInstance->Montage_Play(HitReaction_Montage, 1.f, EMontagePlayReturnType::Duration, 0.f);
}






