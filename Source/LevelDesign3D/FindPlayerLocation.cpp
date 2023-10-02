// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "AIController.h"
#include "AI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindPlayerLocation::UFindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAI_Controller* AIController = Cast<AAI_Controller>(OwnerComp.GetAIOwner());

	FVector Player_Location = player->GetActorLocation();

	/*if (IsSearching == true)
	{
		FNavLocation Location;

		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		if (NavSystem != nullptr && NavSystem->GetRandomPointInNavigableRadius(Player_Location, Search_Radius, Location))
		{
			AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);

		}
	}*/
	/*else
	{*/

		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Player_Location);

	/*}*/

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Type();
}
