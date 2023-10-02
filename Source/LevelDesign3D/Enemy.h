// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class LEVELDESIGN3D_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BulletHit(float DeltaTime);

	UAnimInstance* AnimInstance;

	bool ISDamageTaken = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		int EnemyDamageTaken = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		bool Is_Dead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UAnimMontage* HitReaction_Montage;

	float HitReactionTime = 0;

	bool Bullet_Hit = false;

	int hitCounter = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		float Enemy_Health = 100;

	UFUNCTION(BlueprintCallable)
		void DamageTaken(int BulletDMG);

	bool EnemyAgro = false;

	bool IsHit;


};
