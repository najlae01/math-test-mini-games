// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NpcController.generated.h"

class ANPC;

/**
 * 
 */
UCLASS(BlueprintType)
class MATHORIA_API ANpcController : public AAIController
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


private:
	UFUNCTION()
	void SetupCapsuleComponent();

	UPROPERTY()
	ANPC* CharacterRef;
	
};
