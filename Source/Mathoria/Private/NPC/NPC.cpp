// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "NPC/NpcController.h"
#include "Player/MathoriaPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "UI/NpcDialogueWidget.h"

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and set up the collision box
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent);
    CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
    CollisionBox->SetRelativeScale3D(FVector(15.0f, 15.0f, 4.0f));
    CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, -43.0f));
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    // Bind overlap events
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnPlayerEnterRange);
    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnPlayerExitRange);

    // Create and set up the interact widget component
    InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComponent"));
    InteractWidgetComponent->SetupAttachment(RootComponent);
    InteractWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    InteractWidgetComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    InteractWidgetComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    InteractWidgetComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
    InteractWidgetComponent->SetDrawSize(FVector2D(420.0f, 90.0f));
    InteractWidgetComponent->SetVisibility(false);

    // Initialize variables
    IsTalkingToPlayer = false;

    Name = "Einstein";
    Dialogue = "Welcome to mathoria";
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();

    InteractWidgetComponent->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
    InteractWidgetComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    InteractWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));

    // Set the interact widget to the provided blueprint
    //if (InteractNPCWidgetClass)
    //{
    //    InteractWidget = CreateWidget<UUserWidget>(GetWorld(), InteractNPCWidgetClass);
    //    if (InteractWidget)
    //    {
    //        // Assign the widget to the widget component
    //        InteractWidgetComponent->SetWidget(InteractWidget);
    //    }
    //}
  
    // Run the Behavior Tree if it's assigned
    if (BehaviorTree)
    {
        ANpcController* AIController = Cast<ANpcController>(GetController());
        if (AIController)
        {
            AIController->RunBehaviorTree(BehaviorTree);
        }
    }
}

UBehaviorTree* ANPC::GetBehaviorTree() const
{
    return BehaviorTree;
}

void ANPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Ensure InteractWidgetComponent is valid
    if (!InteractWidgetComponent)
    {
        return;
    }

    // Only rotate the widget if not talking to the player
    if (!IsTalkingToPlayer)
    {
        // Get the player controller
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (!PlayerController)
        {
            return;
        }

        // Get the player's pawn (character)
        APawn* PlayerPawn = PlayerController->GetPawn();
        if (!PlayerPawn)
        {
            return;
        }

        // Calculate the rotation to face the player
        FVector WidgetLocation = InteractWidgetComponent->GetComponentLocation();
        FVector PlayerLocation = PlayerPawn->GetActorLocation();
        FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(WidgetLocation, PlayerLocation);

        // Set the widget's rotation (only yaw, ignore pitch and roll)
        InteractWidgetComponent->SetWorldRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
    }
}

void ANPC::OnPlayerEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapping actor has the "Player" tag
    if (OtherActor && OtherActor->ActorHasTag(FName("Player")))
    {
        PlayerCharacter = Cast<AMathoriaPlayer>(OtherActor);

        // Show the interact widget (e.g., "Click the button in the widget to talk")
        if (!IsTalkingToPlayer && InteractWidgetComponent)
        {
            InteractWidgetComponent->SetVisibility(true);
        }
    }
    else
    {
        IsTalkingToPlayer = false;
    }
}

void ANPC::OnPlayerExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor == PlayerCharacter)
    {
        PlayerCharacter = nullptr;

        // End dialogue if the player leaves the range
        if (IsTalkingToPlayer)
        {
            EndDialogue();
        }

        // Hide the interact widget
        if (InteractWidgetComponent)
        {
            InteractWidgetComponent->SetVisibility(false);
        }

    }
}

void ANPC::StartDialogue()
{
    if (PlayerCharacter)
    {
        // Set the talking flag
        IsTalkingToPlayer = true;

        // Create and display the dialogue widget
        if (!NpcDialogueWidget)
        {
            NpcDialogueWidget = CreateWidget<UUserWidget>(GetWorld(), NpcDialogueWidgetClass);

            if (UNpcDialogueWidget* DialogueWidget = Cast<UNpcDialogueWidget>(NpcDialogueWidget))
            {
                DialogueWidget->InitializeDialogue(this);
            }
        }
        if (NpcDialogueWidget && !NpcDialogueWidget->IsInViewport())
        {
            NpcDialogueWidget->AddToViewport(2);
            NpcDialogueWidget->SetVisibility(ESlateVisibility::Visible);
        }

    }
}

void ANPC::EndDialogue()
{
    // Reset the talking flag
    IsTalkingToPlayer = false;

    // Remove the dialogue widget from the viewport
    if (NpcDialogueWidget)
    {
        NpcDialogueWidget->RemoveFromViewport();
    }
}
