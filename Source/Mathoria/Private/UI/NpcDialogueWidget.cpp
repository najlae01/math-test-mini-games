// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NpcDialogueWidget.h"
#include "NPC/NPC.h"

void UNpcDialogueWidget::InitializeDialogue(ANPC* InNPC)
{
    NPCReference = InNPC;
}