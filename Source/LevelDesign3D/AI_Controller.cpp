// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "LevelDesign3DCharacter.h"

AAI_Controller::AAI_Controller()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));

	SetupPerception();
}

//void AAI_Controller::OnTargetDetected(AActor* Actor, FAIStimulus stimulus)
//{
//	if (ALevelDesign3DCharacter* character = Cast<ALevelDesign3DCharacter>(Actor))
//	{
//		Blackboard->SetValueAsBool(FName(TEXT("CanSeePlayer")), stimulus.WasSuccessfullySensed());
//	}
//}

void AAI_Controller::SetupPerception()
{
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	if (sight_config)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		sight_config->SightRadius = 600.0f;
		sight_config->LoseSightRadius = sight_config->SightRadius + 25.0f;
		sight_config->PeripheralVisionAngleDegrees = 90.0f;
		sight_config->SetMaxAge(5.0f);
		sight_config->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		sight_config->DetectionByAffiliation.bDetectEnemies =
			sight_config->DetectionByAffiliation.bDetectFriendlies =
			sight_config->DetectionByAffiliation.bDetectNeutrals = true;

		// add sight configuration component to perception component
		GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
		//GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Controller::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*sight_config);
	}
}

void AAI_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}

	Blackboard->SetValueAsBool(FName(TEXT("Is_Chasing")), false);
}

void AAI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;

	if (Timer >= 4.2)
	{
		Blackboard->SetValueAsBool(FName(TEXT("Is_Chasing")), true);
	}
}

void AAI_Controller::AIPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);

	if (Blackboard != nullptr && BehaviorTree != nullptr)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);


		Enemy = Cast<AEnemy>(InPawn);

		

	}
}
