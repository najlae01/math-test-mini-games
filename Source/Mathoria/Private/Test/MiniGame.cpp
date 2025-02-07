// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/MiniGame.h"


void UMiniGame::StartMiniGame()
{

}

bool UMiniGame::CheckSuccess(int32 RequiredCorrectAnswers)
{
	return PlayerCorrectAnswers >= RequiredCorrectAnswers;
}
