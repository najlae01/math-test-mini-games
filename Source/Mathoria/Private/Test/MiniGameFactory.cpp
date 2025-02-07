// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/MiniGameFactory.h"
#include "Test/ReadingNumbersOneDigitMiniGame.h"
#include "Test/ReadingNumbersTwoDigitsMiniGame.h"
#include "Test/AdditionMiniGame.h"
#include "Test/SubtractionMiniGame.h"
#include "Test/MultiplicationMiniGame.h"
#include "Test/DivisionMiniGame.h"
#include "Test/ProblemMiniGame.h"


UMiniGameFactory* UMiniGameFactory::Get()
{
    static UMiniGameFactory* Instance = NewObject<UMiniGameFactory>();
    return Instance;
}

UMiniGame* UMiniGameFactory::CreateMiniGame(EMiniGameName MiniGameName)
{
    if (MiniGameName == EMiniGameName::ReadingNumbersOneDigit) return NewObject<UReadingNumbersOneDigitMiniGame>();
    if (MiniGameName == EMiniGameName::ReadingNumbersTwoDigits) return NewObject<UReadingNumbersTwoDigitsMiniGame>();
    if (MiniGameName == EMiniGameName::Addition) return NewObject<UAdditionMiniGame>();
    if (MiniGameName == EMiniGameName::Subtraction) return NewObject<USubtractionMiniGame>();
    if (MiniGameName == EMiniGameName::Multiplication) return NewObject<UMultiplicationMiniGame>();
    if (MiniGameName == EMiniGameName::Division) return NewObject<UDivisionMiniGame>();
    if (MiniGameName == EMiniGameName::Problem) return NewObject<UProblemMiniGame>();
    return nullptr;
}