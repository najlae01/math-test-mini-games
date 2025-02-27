// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

// Forward declarations
class UBoxComponent;
class UWidgetComponent;
class UUserWidget;
class AMathoriaPlayer;

UCLASS(BlueprintType)
class MATHORIA_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
    ANPC();

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Identity")
    FString Name;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dialogue")
    FString Dialogue;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Collision box for interaction range
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Dialogue")
    TObjectPtr<UBoxComponent> CollisionBox;

    //// Widget component to display interaction prompt  (e.g., "Click the button in the widget to talk")
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Dialogue")
    TObjectPtr<UWidgetComponent> InteractWidgetComponent;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Dialogue")
    TSubclassOf<UUserWidget> InteractNPCWidgetClass;

    // Reference to the interact widget blueprint (e.g., "Click the button in the widget to talk")
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue", meta = (EditInline = "true"))
    TObjectPtr<UUserWidget> InteractWidget;

    // Flag to check if the NPC is currently talking to the player
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Dialogue")
    bool IsTalkingToPlayer;

    // Reference to the NPC dialogue widget blueprint
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Dialogue")
    TSubclassOf<UUserWidget> NpcDialogueWidgetClass;

    // Reference to the NPC dialogue widget blueprint
    UPROPERTY(BlueprintReadWrite, Category = "Dialogue", meta = (EditInline = "true"))
    TObjectPtr<UUserWidget> NpcDialogueWidget;

    UFUNCTION()
    UBehaviorTree* GetBehaviorTree() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // AI Behavior Tree
    UPROPERTY(EditAnywhere, Category = "AI")
    UBehaviorTree* BehaviorTree;

    // Start dialogue with the player
    UFUNCTION(BlueprintCallable)
    void StartDialogue();

private:
    // Reference to the player character
    AActor* PlayerCharacter;

    // Called when the player enters the interaction range
    UFUNCTION()
    void OnPlayerEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Called when the player exits the interaction range
    UFUNCTION()
    void OnPlayerExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


    // End dialogue with the player
    void EndDialogue();
};
