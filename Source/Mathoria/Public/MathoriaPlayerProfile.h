// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FirebaseFeatures.h"
#include "Database/DatabaseReference.h"
#include "Avatar/AvatarCustomizationManager.h"
#include "Test/GradeLevel.h"
#include "Test/MiniGameObserver.h"
#include "MathoriaPlayerProfile.generated.h"
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MATHORIA_API UMathoriaPlayerProfile : public UObject, public IMiniGameObserver
{
	GENERATED_BODY()

public:

	UMathoriaPlayerProfile();

	void OnMiniGameCompleted(EMiniGameName MiniGameName, bool bResult) override;

	// Player Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info", Replicated)
	FString PlayerName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info", Replicated)
	EGradeLevel SchoolGrade;

	// Resources
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources", Replicated)
	int32 Coins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources", Replicated)
	int32 Gems;

	// Progress
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress", Replicated)
	int32 GameLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress", Replicated)
	int32 MathPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress", Replicated)
	TArray<FString> CompletedTasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
	TMap<FString, int32> Skills;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", Replicated)
	int32 TimeSpent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", Replicated)
	int32 QuestionsSolved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", Replicated)
	float Accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", Replicated)
	int32 HintsUsed;

	// Customization
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	TMap<FString, FString> AvatarCustomizations;

	// Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", Replicated)
	TArray<FString> InventoryItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", Replicated)
	TArray<FString> ClothingItems;

	// TEST
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	bool IsAuthenticatedByTeacher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	FString LinkedTeacherID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", Replicated)
	EGradeLevel MathLevel; // Real math level of the player resulted after taking TaRL test

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	FString TestQuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	float TestTimeRemaining;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	int32 TimesTestPaused;

	// Save and Load Methods
	UFUNCTION(BlueprintCallable, Category = "Firebase")
	bool SavePlayerData(FString FirebasePlayerId);

	UFUNCTION(BlueprintCallable, Category = "Firebase")
	bool LoadPlayerData(FString FirebasePlayerId);

	// Helper function to initialize Firebase reference
	void InitializeDatabaseReference(FString FirebasePlayerId);


	// Customization Manager Reference
	UPROPERTY() 
	TObjectPtr<UAvatarCustomizationManager> CustomizationManager;

private:
	// Firebase reference
	UPROPERTY()
	UDatabaseReference* PlayerDatabaseRef;

	EGradeLevel MapIntToSchoolGradeEnum(int32 SchoolGradeInt);

	int32 MapSchoolGradeEnumToInt(EGradeLevel SchoolGradeEnum);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
