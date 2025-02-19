// Fill out your copyright notice in the Description page of Project Settings.


#include "MathoriaPlayerProfile.h"
#include "Database/Database.h"
#include "Database/DatabaseReference.h"
#include "FirebaseSdk/FirebaseVariant.h"
#include "Auth/User.h"
#include <Net/UnrealNetwork.h>
#include "Serialization/JsonSerializer.h"    
#include "Dom/JsonObject.h"             
#include "Serialization/JsonWriter.h" 
#include "Kismet/GameplayStatics.h"
#include "MathoriaGameInstance.h"


UMathoriaPlayerProfile::UMathoriaPlayerProfile()
{

}


void UMathoriaPlayerProfile::OnMiniGameCompleted(EMiniGameName MiniGameName, bool bResult)
{
    UMathoriaGameInstance* GameInstance = Cast<UMathoriaGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (GameInstance && GameInstance->TarlManager)
    {
        // DisplayMiniGameResult();
        // DisplayPlayerScore();
    }
}


void UMathoriaPlayerProfile::InitializeDatabaseReference(FString FirebasePlayerId)
{
    UE_LOG(LogTemp, Log, TEXT("Authenticated FirebasePlayerId: %s"), *FirebasePlayerId);  // Log the ID
    // Get the Firebase database reference
    if (UDatabaseReference* DatabaseRef = UDatabase::GetInstanceReference())
    {
        if (DatabaseRef && DatabaseRef->IsValid())
        {
            // Reference to the "players" node
            DatabaseRef = DatabaseRef->Child("players");

            // Reference to the specific player using FirebasePlayerId
            PlayerDatabaseRef = DatabaseRef->Child(FirebasePlayerId);

            UE_LOG(LogTemp, Log, TEXT("Successfully initialized PlayerDatabaseRef for player '%s'."), *FirebasePlayerId);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get a valid database reference."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Firebase Database instance is null."));
    }
}


bool UMathoriaPlayerProfile::SavePlayerData(FString FirebasePlayerId)
{
    InitializeDatabaseReference(FirebasePlayerId);
    if (!PlayerDatabaseRef || !PlayerDatabaseRef->IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerDatabaseRef is invalid. Ensure Firebase is initialized."));
        return false;
    }

    // Use a success flag
    bool bOperationSuccessful = true;

    // Create the save callback
    FDatabaseCallback SaveCallback = FDatabaseCallback::CreateLambda([&bOperationSuccessful](EFirebaseDatabaseError Error) {
        if (Error == EFirebaseDatabaseError::None)
        {
            UE_LOG(LogTemp, Log, TEXT("Player data saved successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to save player data: %d"), static_cast<int32>(Error));
            bOperationSuccessful = false; // Mark as failed if any error occurs
        }
        });

    // Save player data to Firebase
    PlayerDatabaseRef->Child("player_name")->SetValue(FFirebaseVariant(PlayerName), SaveCallback);
    PlayerDatabaseRef->Child("game_level")->SetValue(FFirebaseVariant(GameLevel), SaveCallback);
    PlayerDatabaseRef->Child("coins")->SetValue(FFirebaseVariant(Coins), SaveCallback);
    PlayerDatabaseRef->Child("gems")->SetValue(FFirebaseVariant(Gems), SaveCallback);
    PlayerDatabaseRef->Child("math_points")->SetValue(FFirebaseVariant(MathPoints), SaveCallback);

    int32 GradeInt = MapSchoolGradeEnumToInt(SchoolGrade);
    PlayerDatabaseRef->Child("school_grade")->SetValue(FFirebaseVariant(GradeInt), SaveCallback);

    int32 MathLevelInt = MapSchoolGradeEnumToInt(MathLevel);
    PlayerDatabaseRef->Child("math_level")->SetValue(FFirebaseVariant(MathLevelInt), SaveCallback);


    // Serialize CompletedTasks array to a JSON string
    FString CompletedTasksJson;
    TArray<TSharedPtr<FJsonValue>> CompletedTasksJsonArray;
    for (const FString& Task : CompletedTasks)
    {
        CompletedTasksJsonArray.Add(MakeShareable(new FJsonValueString(Task)));
    }

    // Create JSON Writer for CompletedTasks
    TSharedRef<TJsonWriter<TCHAR>> CompletedTasksWriter = TJsonWriterFactory<TCHAR>::Create(&CompletedTasksJson);
    TSharedRef<FJsonObject> CompletedTasksJsonObject = MakeShareable(new FJsonObject());
    CompletedTasksJsonObject->SetArrayField(TEXT("completed_tasks"), CompletedTasksJsonArray);
    FJsonSerializer::Serialize(CompletedTasksJsonObject, CompletedTasksWriter);

    // Use CompletedTasksJson in the Firebase call
    PlayerDatabaseRef->Child("completed_tasks")->SetValue(FFirebaseVariant(CompletedTasksJson), SaveCallback);


    // Serialize Skills map to a JSON string
    FString SkillsJson;
    TSharedRef<TJsonWriter<TCHAR>> SkillsWriter = TJsonWriterFactory<TCHAR>::Create(&SkillsJson);
    TSharedRef<FJsonObject> SkillsJsonObject = MakeShareable(new FJsonObject());
    for (const TPair<FString, int32>& Skill : Skills)
    {
        SkillsJsonObject->SetNumberField(Skill.Key, Skill.Value);
    }
    FJsonSerializer::Serialize(SkillsJsonObject, SkillsWriter);

    PlayerDatabaseRef->Child("skills")->SetValue(FFirebaseVariant(SkillsJson), SaveCallback);


    // Save other data (time_spent, accuracy, etc.) as usual
    PlayerDatabaseRef->Child("time_spent")->SetValue(FFirebaseVariant(TimeSpent), SaveCallback);
    PlayerDatabaseRef->Child("questions_solved")->SetValue(FFirebaseVariant(QuestionsSolved), SaveCallback);
    PlayerDatabaseRef->Child("accuracy")->SetValue(FFirebaseVariant(Accuracy), SaveCallback);
    PlayerDatabaseRef->Child("hints_used")->SetValue(FFirebaseVariant(HintsUsed), SaveCallback);

    // Serialize AvatarCustomizations map to a JSON string
    FString AvatarCustomizationJson;
    TSharedRef<TJsonWriter<TCHAR>> AvatarCustomizationWriter = TJsonWriterFactory<TCHAR>::Create(&AvatarCustomizationJson);
    TSharedRef<FJsonObject> AvatarCustomizationJsonObject = MakeShareable(new FJsonObject());
    for (const TPair<FString, FString>& Customization : AvatarCustomizations)
    {
        AvatarCustomizationJsonObject->SetStringField(Customization.Key, Customization.Value);
    }
    FJsonSerializer::Serialize(AvatarCustomizationJsonObject, AvatarCustomizationWriter);

    PlayerDatabaseRef->Child("avatar_customizations")->SetValue(FFirebaseVariant(AvatarCustomizationJson), SaveCallback);


    // Serialize InventoryItems array to a JSON string
    FString InventoryItemsJson;
    TArray<TSharedPtr<FJsonValue>> InventoryItemsJsonArray;
    for (const FString& Item : InventoryItems)
    {
        InventoryItemsJsonArray.Add(MakeShareable(new FJsonValueString(Item)));
    }

    // Create JSON Writer for InventoryItems
    TSharedRef<TJsonWriter<TCHAR>> InventoryItemsWriter = TJsonWriterFactory<TCHAR>::Create(&InventoryItemsJson);
    TSharedRef<FJsonObject> InventoryItemsJsonObject = MakeShareable(new FJsonObject());
    InventoryItemsJsonObject->SetArrayField(TEXT("inventory_items"), InventoryItemsJsonArray);
    FJsonSerializer::Serialize(InventoryItemsJsonObject, InventoryItemsWriter);

    PlayerDatabaseRef->Child("inventory_items")->SetValue(FFirebaseVariant(InventoryItemsJson), SaveCallback);


    // Serialize ClothingItems array to a JSON string
    FString ClothingItemsJson;
    TArray<TSharedPtr<FJsonValue>> ClothingItemsJsonArray;
    for (const FString& Item : ClothingItems)
    {
        ClothingItemsJsonArray.Add(MakeShareable(new FJsonValueString(Item)));
    }

    // Create JSON Writer for ClothingItems
    TSharedRef<TJsonWriter<TCHAR>> ClothingItemsWriter = TJsonWriterFactory<TCHAR>::Create(&ClothingItemsJson);
    TSharedRef<FJsonObject> ClothingItemsJsonObject = MakeShareable(new FJsonObject());
    ClothingItemsJsonObject->SetArrayField(TEXT("clothing_items"), ClothingItemsJsonArray);
    FJsonSerializer::Serialize(ClothingItemsJsonObject, ClothingItemsWriter);

    PlayerDatabaseRef->Child("clothing_items")->SetValue(FFirebaseVariant(ClothingItemsJson), SaveCallback);


    // Return the success flag
    return bOperationSuccessful;
}


bool UMathoriaPlayerProfile::LoadPlayerData(FString FirebasePlayerId)
{
    InitializeDatabaseReference(FirebasePlayerId);
    if (!PlayerDatabaseRef || !PlayerDatabaseRef->IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerDatabaseRef is invalid. Ensure Firebase is initialized."));
        return false;
    }

    // Success flag
    bool bOperationSuccessful = true;

    // Define the callback
    FSnapshotCallback Callback = FSnapshotCallback::CreateLambda([this, &bOperationSuccessful](EFirebaseDatabaseError Error, const UDataSnapshot* Snapshot) {
        if (Error == EFirebaseDatabaseError::None)
        {
            if (Snapshot && Snapshot->IsValid())
            {
                if (Snapshot->HasChild("player_name"))
                {
                    PlayerName = Snapshot->GetChild("player_name")->GetValue().AsString();
                    GameLevel = Snapshot->GetChild("game_level")->GetValue().AsInt32();
                    Coins = Snapshot->GetChild("coins")->GetValue().AsInt32();
                    Gems = Snapshot->GetChild("gems")->GetValue().AsInt32();
                    MathPoints = Snapshot->GetChild("math_points")->GetValue().AsInt32();

                    int32 GradeInt = Snapshot->GetChild("school_grade")->GetValue().AsInt32();
                    UE_LOG(LogTemp, Warning, TEXT("Retrieved school grade from Firebase: %d"), GradeInt);
                    SchoolGrade = MapIntToSchoolGradeEnum(GradeInt);
                    

                    int32 MathLevelInt = Snapshot->GetChild("math_level")->GetValue().AsInt32();
                    MathLevel = MapIntToSchoolGradeEnum(MathLevelInt);

                    if (Snapshot->HasChild("completed_tasks"))
                    {
                        // Convert Firebase array to Unreal array
                        const TArray<FFirebaseVariant> FirebaseArray = Snapshot->GetChild("completed_tasks")->GetValue().AsArray();
                        for (const FFirebaseVariant& Task : FirebaseArray)
                        {
                            CompletedTasks.Add(Task.AsString());  // Assuming tasks are strings
                        }
                    }

                    if (Snapshot->HasChild("skills"))
                    {
                        // Convert Firebase map to Unreal map
                        const TMap<FFirebaseVariant, FFirebaseVariant> FirebaseMap = Snapshot->GetChild("skills")->GetValue().AsMap();
                        for (const auto& Pair : FirebaseMap)
                        {
                            Skills.Add(Pair.Key.AsString(), Pair.Value.AsInt32());
                        }
                    }

                    TimeSpent = Snapshot->GetChild("time_spent")->GetValue().AsInt32();
                    QuestionsSolved = Snapshot->GetChild("questions_solved")->GetValue().AsInt32();
                    Accuracy = Snapshot->GetChild("accuracy")->GetValue().AsFloat();
                    HintsUsed = Snapshot->GetChild("hints_used")->GetValue().AsInt32();

                    if (Snapshot->HasChild("avatar_customizations"))
                    {
                        // Convert Firebase map to Unreal map
                        const TMap<FFirebaseVariant, FFirebaseVariant> FirebaseMap = Snapshot->GetChild("avatar_customizations")->GetValue().AsMap();
                        for (const auto& Pair : FirebaseMap)
                        {
                            AvatarCustomizations.Add(Pair.Key.AsString(), Pair.Value.AsString());  // Assuming customizations are key-value pairs of strings
                        }
                    }

                    if (Snapshot->HasChild("inventory_items"))
                    {
                        // Convert Firebase array to Unreal array
                        const TArray<FFirebaseVariant> FirebaseArray = Snapshot->GetChild("inventory_items")->GetValue().AsArray();
                        for (const FFirebaseVariant& Item : FirebaseArray)
                        {
                            InventoryItems.Add(Item.AsString());  // Assuming items are strings
                        }
                    }

                    if (Snapshot->HasChild("clothing_items"))
                    {
                        // Convert Firebase array to Unreal array
                        const TArray<FFirebaseVariant> FirebaseArray = Snapshot->GetChild("clothing_items")->GetValue().AsArray();
                        for (const FFirebaseVariant& Item : FirebaseArray)
                        {
                            ClothingItems.Add(Item.AsString());  // Assuming clothing items are strings
                        }
                    }

                    UE_LOG(LogTemp, Log, TEXT("Player data loaded successfully."));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Player data is incomplete or missing."));
                    bOperationSuccessful = false;
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Snapshot is invalid."));
                bOperationSuccessful = false;
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load player data: %d"), static_cast<int32>(Error));
            bOperationSuccessful = false;
        }
        });

    // Call GetValue with the callback
    PlayerDatabaseRef->GetValue(Callback);

    // Return the success flag
    return bOperationSuccessful;
}

EGradeLevel UMathoriaPlayerProfile::MapIntToSchoolGradeEnum(int32 SchoolGradeInt)
{
    UE_LOG(LogTemp, Warning, TEXT("Inside MapIntToSchoolGradeEnum with value: %d"), SchoolGradeInt);
    switch (SchoolGradeInt)
    {
    case 1:
        return EGradeLevel::One;
    case 2:
        return EGradeLevel::Two;
    case 3:
        return EGradeLevel::Three;
    case 4:
        return EGradeLevel::Four;
    case 5:
        return EGradeLevel::Five;
    case 6:
        return EGradeLevel::Six;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Invalid school grade value: %d. Defaulting to Grade 1."), SchoolGradeInt);
        return EGradeLevel::One; 
    }
}

int32 UMathoriaPlayerProfile::MapSchoolGradeEnumToInt(EGradeLevel SchoolGradeEnum)
{
    switch (SchoolGradeEnum)
    {
    case EGradeLevel::One:
        return 1;
    case EGradeLevel::Two:
        return 2;
    case EGradeLevel::Three:
        return 3;
    case EGradeLevel::Four:
        return 4;
    case EGradeLevel::Five:
        return 5;
    case EGradeLevel::Six:
        return 6;
    default:
        return 1; 
    }
}


void UMathoriaPlayerProfile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Replicate player data properties
    DOREPLIFETIME(UMathoriaPlayerProfile, PlayerName);
    DOREPLIFETIME(UMathoriaPlayerProfile, SchoolGrade);
    DOREPLIFETIME(UMathoriaPlayerProfile, GameLevel);
    DOREPLIFETIME(UMathoriaPlayerProfile, Coins);
    DOREPLIFETIME(UMathoriaPlayerProfile, Gems);
    DOREPLIFETIME(UMathoriaPlayerProfile, MathPoints);
    DOREPLIFETIME(UMathoriaPlayerProfile, CompletedTasks); 
    DOREPLIFETIME(UMathoriaPlayerProfile, InventoryItems);
    DOREPLIFETIME(UMathoriaPlayerProfile, ClothingItems); 
    DOREPLIFETIME(UMathoriaPlayerProfile, TimeSpent); 
    DOREPLIFETIME(UMathoriaPlayerProfile, QuestionsSolved);
    DOREPLIFETIME(UMathoriaPlayerProfile, Accuracy);
    DOREPLIFETIME(UMathoriaPlayerProfile, HintsUsed);
    DOREPLIFETIME(UMathoriaPlayerProfile, MathLevel);
}

