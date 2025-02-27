// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NpcController.h"
#include "NPC/NPC.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"


void ANpcController::BeginPlay()
{
	Super::BeginPlay();
}

void ANpcController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetBlackboardComponent()->SetValueAsBool("IsTalkingToPlayer", CharacterRef->IsTalkingToPlayer);
}

void ANpcController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CharacterRef = Cast<ANPC>(InPawn);
	if (CharacterRef)
	{
		if (UBehaviorTree* const tree = CharacterRef->GetBehaviorTree())
		{
			UBlackboardComponent* board;
			UseBlackboard(tree->BlackboardAsset, board);
			Blackboard = board;
			RunBehaviorTree(tree);
		}
		FTimerHandle CapsuleSetupHandle;
		GetWorldTimerManager().SetTimer(CapsuleSetupHandle, this, &ANpcController::SetupCapsuleComponent, 0.1f, false);
	}

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	// Check if the navigation system is valid
	if (NavSystem)
	{
		// Rebuild the navigation data
		NavSystem->Build();
		UE_LOG(LogTemp, Warning, TEXT("NavMesh built."));
	}
}

void ANpcController::SetupCapsuleComponent()
{
	if (CharacterRef->FindComponentByClass<UCapsuleComponent>())
	{
		UE_LOG(LogTemp, Display, TEXT("Capsule retrieved."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Capsule not retrieved."));
	}
}