// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MathoriaUserWidget.h"
#include "NpcDialogueWidget.generated.h"

class ANPC;

/**
 * 
 */
UCLASS()
class MATHORIA_API UNpcDialogueWidget : public UMathoriaUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void InitializeDialogue(ANPC* InNPC);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    ANPC* NPCReference;
};
