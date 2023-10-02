// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "Perception/AIPerceptionTypes.h"
#include "AI_Controller.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class LEVELDESIGN3D_API AAI_Controller : public AAIController
{
	GENERATED_BODY()

public:
	AAI_Controller();

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (ALlowPrivateAccess = true))
		UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (ALlowPrivateAccess = true))
		UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (ALlowPrivateAccess = true))
		UBlackboardComponent* BlackBoardComponent;

	class UAISenseConfig_Sight* sight_config;

	AEnemy* Enemy;


	/*UFUNCTION()
		void OnTargetDetected(AActor* Actor, FAIStimulus stimulus);*/

	void SetupPerception();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AIPossess(APawn* const InPawn);

	float Timer = 0;
	
};
