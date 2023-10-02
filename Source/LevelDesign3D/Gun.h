// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class LEVELDESIGN3D_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* GunComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "GUN")
	int GunAmmo;

	FVector Start;
	FVector End;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUN")
	FVector LineTraceOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUN")
	float BulletSpread;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int CurrentAmmo;

	UPROPERTY(EditAnywhere, Category = "GUN")
	int RateOfFire;

	void Shoot(UCameraComponent* FollowCamera, AActor* Player, bool IsAds);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun)
		UAnimMontage* FireMontage;

	int Gun_UI_Magazine;


};
