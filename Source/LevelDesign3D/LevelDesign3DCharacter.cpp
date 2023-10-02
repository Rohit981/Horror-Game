// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelDesign3DCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

//////////////////////////////////////////////////////////////////////////
// ALevelDesign3DCharacter

ALevelDesign3DCharacter::ALevelDesign3DCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input



void ALevelDesign3DCharacter::SetupStimuls()
{
	stimulSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimul"));

	stimulSource->RegisterForSense(TSubclassOf<UAISense>());
	stimulSource->RegisterWithPerceptionSystem();
}

void ALevelDesign3DCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("ADS", IE_Pressed, this, &ALevelDesign3DCharacter::Adsing);
	PlayerInputComponent->BindAction("ADS", IE_Released, this, &ALevelDesign3DCharacter::NotAdsing);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ALevelDesign3DCharacter::Firing);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ALevelDesign3DCharacter::NotFiring);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALevelDesign3DCharacter::Interact);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALevelDesign3DCharacter::Sprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALevelDesign3DCharacter::StopSprinting);


	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ALevelDesign3DCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ALevelDesign3DCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ALevelDesign3DCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ALevelDesign3DCharacter::LookUpAtRate);

	Health = 100;

}

void ALevelDesign3DCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	
	

	HUD->CrossHair_Ref->SetVisibility(ESlateVisibility::Hidden);
	HUD->AmmoAndHealth_Ref->SetVisibility(ESlateVisibility::Hidden);


	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("Zoom"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);

	}

	


}

void ALevelDesign3DCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);

	//GetCharacterMovement()->bOrientRotationToMovement = true;

	AnimInstance = GetMesh()->GetAnimInstance();

	AdsCharacterOrientation();

	InteractDetection();
	SpawnGun();


	if (has_Weapon_PickedUP == true)
	{
		UI_Magazine = Gun->CurrentAmmo;

	}

}




void ALevelDesign3DCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALevelDesign3DCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALevelDesign3DCharacter::Adsing()
{
	if (has_Weapon_PickedUP == true)
	{
		IsAdsing = true;
		CurveTimeline.PlayFromStart();

		HUD->CrossHair_Ref->SetVisibility(ESlateVisibility::Visible);
		HUD->AmmoAndHealth_Ref->SetVisibility(ESlateVisibility::Visible);


		GetCharacterMovement()->MaxWalkSpeed = 150;

	}
}

void ALevelDesign3DCharacter::NotAdsing()
{
	if (has_Weapon_PickedUP == true)
	{
		IsAdsing = false;
		CurveTimeline.Reverse();

		HUD->CrossHair_Ref->SetVisibility(ESlateVisibility::Hidden);
		HUD->AmmoAndHealth_Ref->SetVisibility(ESlateVisibility::Hidden);

		GetCharacterMovement()->MaxWalkSpeed = 600;
	}



}

void ALevelDesign3DCharacter::Zoom(float Value)
{

	if (IsAdsing)
	{
		StartFOV = 40;

		EndFOV = 20;
	}


	float NewFOV = FMath::Lerp(StartFOV, EndFOV, Value);

	FollowCamera->FieldOfView = NewFOV;
}

void ALevelDesign3DCharacter::AdsCharacterOrientation()
{
	if (IsAdsing == true)
	{
		FollowCamera->bUsePawnControlRotation = true;

		bUseControllerRotationYaw = FollowCamera->bUsePawnControlRotation;
		bUseControllerRotationPitch = FollowCamera->bUsePawnControlRotation;

		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		FollowCamera->bUsePawnControlRotation = false;

		bUseControllerRotationYaw = FollowCamera->bUsePawnControlRotation;
		bUseControllerRotationPitch = FollowCamera->bUsePawnControlRotation;


		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void ALevelDesign3DCharacter::Firing()
{
	if (has_Weapon_PickedUP == true)
	{
		if (Gun->CurrentAmmo >= 0)
		{
			/*if (Gun->IsGunReloading == false)
			{*/
				FireShot();

				GetWorldTimerManager().SetTimer(Time_Handle_Manager, this, &ALevelDesign3DCharacter::FireShot, Gun->RateOfFire, true);

			/*}*/



		}

	}
}

void ALevelDesign3DCharacter::NotFiring()
{
	GetWorldTimerManager().ClearTimer(Time_Handle_Manager);
}

void ALevelDesign3DCharacter::FireShot()
{
	if (IsAdsing == true)
	{
		Gun->Shoot(FollowCamera, this, IsAdsing);
		AnimInstance->Montage_Play(Gun->FireMontage, 1.f, EMontagePlayReturnType::MontageLength, 0.f);


		if (Gun->CurrentAmmo >= 0)
		{
			Gun->CurrentAmmo -= 1;

			UI_Magazine -= 1;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Magazine: %i"), Gun->CurrentAmmo));

		}
	}
	/*else
	{
		AnimInstance->Montage_Play(Gun->FireMontage, 0.8f, EMontagePlayReturnType::MontageLength, 0.f);

	}*/

	

	
}

void ALevelDesign3DCharacter::SpawnGun()
{

	if (PistolClass != nullptr && has_PickedValue == 0 && has_Weapon_PickedUP == true)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FVector Location = GetActorLocation();
			FRotator Rotation = GetActorRotation();

			Gun = World->SpawnActor<AGun>(PistolClass, Location, Rotation);

			if (Gun != nullptr)
			{
				
				Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Palm_R"));

				has_PickedValue = 1;
	
			}
		}
	}
}



void ALevelDesign3DCharacter::Interact()
{
	if (can_Interact == true)
	{
		Is_Interacting = true;
	}
}

void ALevelDesign3DCharacter::InteractDetection()
{
	FVector Start = this->GetActorLocation();
	FVector End = (FollowCamera->GetForwardVector() * 500) + Start;

	FHitResult OutHit;

	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(FollowCamera->GetOwner());
	ActorsToIgnore.Add(this);
	
	bool IsHit = false;

	IsHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 10, ETraceTypeQuery::TraceTypeQuery3,
		false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true, FLinearColor::Blue, FLinearColor::Green, 1.f);

	if (IsHit == true)
	{
		HUD->Interaction_Ref->SetVisibility(ESlateVisibility::Visible);
		can_Interact = true;

	}
	else
	{
		HUD->Interaction_Ref->SetVisibility(ESlateVisibility::Hidden);
		can_Interact = false;


	}
}

void ALevelDesign3DCharacter::Sprinting()
{

	IsSprinting = true;

}

void ALevelDesign3DCharacter::StopSprinting()
{
	IsSprinting = false;

}

void ALevelDesign3DCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if (GetCharacterMovement()->bOrientRotationToMovement == true)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;
		}

		if (!IsSprinting)
		{
			Value *= 0.7;

		}

		//// find out which way is forward
		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);

		//// get forward vector
		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ALevelDesign3DCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		if (GetCharacterMovement()->bOrientRotationToMovement == true)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;
		}


		if (!IsSprinting)
		{
			Value *= 0.7;

		}
		//// find out which way is right
		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		//// get right vector 
		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}
