// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlendViewTarget.generated.h"

class UBoxComponent;

UCLASS()
class LEVELDESIGN3D_API ABlendViewTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlendViewTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere, Category = "ViewTarget")
		AActor* ViewTarget = nullptr;

	UPROPERTY(EditAnywhere, Category = "ViewTarget")
		float BlendTime = 1.f;

	APlayerController* player;

	APawn* playerPawn;

	float PlayerCamTime = 0;

	int OverlapppedCount = 0;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void EnablePlayerController(float DeltaTime);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool Is_Overlapped = false;



};
