// Fill out your copyright notice in the Description page of Project Settings.


#include "MathoriaPlayerState.h"
#include "Database/Database.h"
#include "Database/DatabaseReference.h"
#include "FirebaseSdk/FirebaseVariant.h"
#include "Auth/User.h"
#include "Test/GradeLevel.h"
#include <Net/UnrealNetwork.h>

AMathoriaPlayerState::AMathoriaPlayerState()
{
    // Create PlayerProfile as a default subobject in the constructor
    if (!PlayerProfile)
    {
        UE_LOG(LogTemp, Warning, TEXT("Creating new PlayerProfile"));
        PlayerProfile = CreateDefaultSubobject<UMathoriaPlayerProfile>(TEXT("PlayerProfile"));
    }
}

void AMathoriaPlayerState::BeginPlay()
{
    Super::BeginPlay();

    // Make sure PlayerProfile is still valid and initialized
    if (!PlayerProfile)
    {
        UE_LOG(LogTemp, Warning, TEXT("Creating new PlayerProfile in BeginPlay"));
        PlayerProfile = CreateDefaultSubobject<UMathoriaPlayerProfile>(TEXT("PlayerProfile"));
    }
}


bool AMathoriaPlayerState::OnSplashScreen()
{
    UUser* const User = FAuth::CurrentUser();
    if (User != nullptr)
    {
        FirebasePlayerId = User->Uid();
        UE_LOG(LogTemp, Log, TEXT("Authenticated FirebasePlayerId: %s"), *FirebasePlayerId);  // Log the ID
        return LoadPlayerData();
    }

    else
    {
        UE_LOG(LogTemp, Error, TEXT("Firebase Authentication is not initialized or user is not logged in."));
        FirebasePlayerId = "Anonymous";  // Default fallback ID
        if (PlayerProfile != nullptr)
        {
            PlayerProfile->PlayerName = "GuestPlayer";
            PlayerProfile->GameLevel = 1;
            PlayerProfile->Coins = 0;
            PlayerProfile->Gems = 0;
            PlayerProfile->MathPoints = 0;

            // Initialize it at Level 1 for now, change it to the value of the player school grade once the teacher registers the student
            PlayerProfile->MathLevel = EGradeLevel::One; 
        }
        IsConnected = false;
        return false;
    }
}


void AMathoriaPlayerState::InitializeDatabaseReference()
{
    UUser* const User = FAuth::CurrentUser();
    if (User != nullptr)
    {
        FirebasePlayerId = User->Uid();
        if (FirebasePlayerId.IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("Player is not authenticated. Cannot load data."));
        }
        else 
        {
            if (PlayerProfile != nullptr)
                PlayerProfile->InitializeDatabaseReference(FirebasePlayerId);
        }
    }

}


bool AMathoriaPlayerState::SavePlayerData()
{
    InitializeDatabaseReference();
    if (FirebasePlayerId.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is not authenticated. Cannot save data."));
        return false;
    }
    else
    {
        if (PlayerProfile != nullptr)
            return PlayerProfile->SavePlayerData(FirebasePlayerId);
        else
            return false;
    }
}

bool AMathoriaPlayerState::LoadPlayerData()
{
    InitializeDatabaseReference(); 

    if (PlayerProfile != nullptr)
    {
        return PlayerProfile->LoadPlayerData(FirebasePlayerId);
    }
    else
    {
        return false;
    }
}



void AMathoriaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Replicate player data properties
    DOREPLIFETIME(AMathoriaPlayerState, FirebasePlayerId);
}

void AMathoriaPlayerState::SetupDisconnection()
{
    // Create the save callback
    FDatabaseCallback SaveCallback = FDatabaseCallback::CreateLambda([](EFirebaseDatabaseError Error) {
        if (Error == EFirebaseDatabaseError::None)
        {
            UE_LOG(LogTemp, Log, TEXT("Player disconnection data saved successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to save player disconnection data: %d"), static_cast<int32>(Error));
        }
    });

    if (UDatabaseReference* PlayersRef = UDatabase::GetInstanceReference())
    {
        if (PlayersRef && PlayersRef->IsValid())
        {
            UDatabaseReference* PlayerDatabaseRef = PlayersRef->ChildFromPaths({ "players", FirebasePlayerId, "is_connected"});
            UE_LOG(LogTemp, Log, TEXT("Successfully initialized PlayerDatabaseRef for player '%s'."), *PlayerProfile->PlayerName);
            PlayerDatabaseRef->Child("is_connected")->GetDisconnectionHandler()->SetValue(false, SaveCallback);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get a valid database reference for 'players'."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Firebase Database instance is null."));
    }
}


void AMathoriaPlayerState::AuthenticateUser(const FString& Uid)
{
    if (Uid.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Authentication failed: Uid is empty."));
        FirebasePlayerId = "Anonymous";  // Fallback to a guest profile

        if (PlayerProfile != nullptr)
        {
            PlayerProfile->PlayerName = "GuestPlayer";
            PlayerProfile->GameLevel = 1;
            PlayerProfile->Coins = 0;
            PlayerProfile->Gems = 0;
            PlayerProfile->MathPoints = 0;
            PlayerProfile->MathLevel = EGradeLevel::One; // Default grade level
        }

        IsConnected = false;
        return;
    }

    // Set FirebasePlayerId and attempt to load data
    FirebasePlayerId = Uid;

    UDatabaseReference* PlayerDatabaseRef;

    if (UDatabaseReference* PlayersRef = UDatabase::GetInstanceReference())
    {
        if (PlayersRef && PlayersRef->IsValid())
        {
            PlayerDatabaseRef = PlayersRef->ChildFromPaths({ "players", FirebasePlayerId, "email" });
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get a valid database reference for 'players'."));
            return;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Firebase Database instance is null."));
        return;
    }

    FString Email = "";

    // Define the callback for database retrieval
    FSnapshotCallback Callback = FSnapshotCallback::CreateLambda([this, &Email](EFirebaseDatabaseError Error, const UDataSnapshot* Snapshot) {
        if (Error == EFirebaseDatabaseError::None)
        {
            if (Snapshot && Snapshot->IsValid())
            {
                if (Snapshot->HasChild("email"))
                {
                    Email = Snapshot->GetChild("email")->GetValue().AsString();
                    UE_LOG(LogTemp, Log, TEXT("Email loaded successfully: %s"), *Email);

                    // After loading email, authenticate the user using the email and password
                    FAuth::SignInWithEmailAndPassword(Email, "password", FFirebaseSignInUserCallback::CreateLambda([this](FFirebaseError Error, UUser* User) {
                        if (Error)
                        {
                            UE_LOG(LogTemp, Error, TEXT("Authentication failed: %s"), *Error.Message);
                            IsConnected = false;
                        }
                        else
                        {
                            UE_LOG(LogTemp, Log, TEXT("User signed in successfully: %s"), *User->Uid());
                            IsConnected = true;
                            // Optionally, load player data after successful authentication
                            LoadPlayerData();
                        }
                        }));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Player data is incomplete or missing email."));
                    IsConnected = false;
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Snapshot is invalid."));
                IsConnected = false;
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load player data: %d"), static_cast<int32>(Error));
            IsConnected = false;
        }
        });

    // Call GetValue with the callback to retrieve player data from the Firebase database
    PlayerDatabaseRef->GetValue(Callback);

    UE_LOG(LogTemp, Log, TEXT("Authenticating FirebasePlayerId: %s"), *FirebasePlayerId);
}



UTexture2D* AMathoriaPlayerState::GetHairTexture(EHairStyle HairStyle, EHairColor HairColor)
{
    if (CustomizationManagerClass)
    {
        if (PlayerProfile->CustomizationManager == nullptr)
        {
            PlayerProfile->CustomizationManager = NewObject<UAvatarCustomizationManager>(this, CustomizationManagerClass);
        }
        return PlayerProfile->CustomizationManager->GetHairTexture(HairStyle, HairColor);
    }
    return nullptr;
}

UTexture2D* AMathoriaPlayerState::GetSkinTexture(ESkinColor SkinColor)
{
    if (CustomizationManagerClass)
    {
        if (PlayerProfile->CustomizationManager == nullptr)
        {
            PlayerProfile->CustomizationManager = NewObject<UAvatarCustomizationManager>(this, CustomizationManagerClass);
        }
        return PlayerProfile->CustomizationManager->GetTextureForSkin(SkinColor);
    }
    return nullptr;
}

UTexture2D* AMathoriaPlayerState::GetOutfitTexture(EOutfit Outfit)
{
    if (CustomizationManagerClass)
    {
        if (PlayerProfile->CustomizationManager == nullptr)
        {
            PlayerProfile->CustomizationManager = NewObject<UAvatarCustomizationManager>(this, CustomizationManagerClass);
        }
        return PlayerProfile->CustomizationManager->GetTextureForOutfit(Outfit);
    }
    return nullptr;
}

UTexture2D* AMathoriaPlayerState::GetAccessoryTexture(EAccessory Accessory)
{
    if (CustomizationManagerClass)
    {
        if (PlayerProfile->CustomizationManager == nullptr)
        {
            PlayerProfile->CustomizationManager = NewObject<UAvatarCustomizationManager>(this, CustomizationManagerClass);
        }
        return PlayerProfile->CustomizationManager->GetTextureForAccessory(Accessory);
    }
    return nullptr;
}

UTexture2D* AMathoriaPlayerState::GetFacialExpressionTexture(EFacialExpression Expression)
{
    if (CustomizationManagerClass)
    {
        if (PlayerProfile->CustomizationManager == nullptr)
        {
            PlayerProfile->CustomizationManager = NewObject<UAvatarCustomizationManager>(this, CustomizationManagerClass);
        }
        return PlayerProfile->CustomizationManager->GetTextureForExpression(Expression);
    }
    return nullptr;
}