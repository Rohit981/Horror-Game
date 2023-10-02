// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Components/TimelineComponent.h"
#include "Gun.h"
#include "GameHUD.h"
#include "BlendViewTarget.h"
#include "LevelDesign3DCharacter.generated.h"

UCLASS(config=Game)
class ALevelDesign3DCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ALevelDesign3DCharacter();

	bool has_Weapon_PickedUP = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float TurnRateGamepad;

	UPROPERTY(BlueprintReadWrite)
		bool has_Power = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		float Health;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DelataTime) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	//ADS
	void Adsing();

	void NotAdsing();

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		UCurveFloat* CurveFloat;

	UPROPERTY(BlueprintReadWrite)
		bool IsAdsing = false;

	UPROPERTY(EditAnywhere, Category = Camera)
		float StartFOV;

	UPROPERTY(EditAnywhere, Category = Camera)
		float EndFOV;

	UFUNCTION()
		void Zoom(float Value);

	void AdsCharacterOrientation();

	//Fire
	void Firing();
	
	void NotFiring();

	void FireShot();

	void SpawnGun();

	UPROPERTY(EditDefaultsOnly, Category = Gun)
		TSubclassOf<class AGun> PistolClass;

	FTimerHandle Time_Handle_Manager;

	UPROPERTY(BlueprintReadWrite)
		bool Is_Shooting = false;

	AGun* Gun;

	////Interact
	void Interact();

	void InteractDetection();

	UPROPERTY(BlueprintReadWrite)
	bool Is_Objective_2 = false;

	

	bool can_Interact = false;

	UPROPERTY(BlueprintReadWrite)
		bool Is_Interacting = false;

	// Sprint Character Variables
	void Sprinting();
	void StopSprinting();

	bool IsSprinting = false;

	//Animation
	UAnimInstance* AnimInstance;

	//UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
		AGameHUD* HUD;

	UPROPERTY(BlueprintReadWrite)
		int UI_Magazine = 0;

	

	//AI Functions and Variables
	class UAIPerceptionStimuliSourceComponent* stimulSource;

	void SetupStimuls();

	//Blend Camera
	UPROPERTY(EditAnywhere, Category = Camera)\
		ABlendViewTarget* blendCamera;

	//Weapon Pickup
	int has_PickedValue = 0;
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

