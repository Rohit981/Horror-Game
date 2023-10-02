// Fill out your copyright notice in the Description page of Project Settings.


#include "BlendViewTarget.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlendViewTarget::ABlendViewTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ABlendViewTarget::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABlendViewTarget::BeginPlay()
{
	Super::BeginPlay();

	player = UGameplayStatics::GetPlayerController(this, 0);

	playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
}

// Called every frame
void ABlendViewTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnablePlayerController(DeltaTime);

}

void ABlendViewTarget::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ViewTarget && OverlapppedCount == 0)
	{
		player->SetViewTargetWithBlend(ViewTarget, BlendTime);

		Is_Overlapped = true;

		OverlapppedCount = 1;
	}
}

void ABlendViewTarget::EnablePlayerController(float DeltaTime)
{
	if (Is_Overlapped == true)
	{
		PlayerCamTime += DeltaTime;

		playerPawn->DisableInput(player);

	}
	else
	{
		playerPawn->EnableInput(player);
	}


	if (PlayerCamTime >= 3.2f)
	{
		player->SetViewTargetWithBlend(playerPawn, 1.f);



	}

	if (PlayerCamTime >= 4.2f)
	{
		Is_Overlapped = false;



		PlayerCamTime = 0;

	}
}

