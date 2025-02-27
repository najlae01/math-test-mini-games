// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MathoriaPlayer.h"

// Sets default values
AMathoriaPlayer::AMathoriaPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Player"));

}

// Called when the game starts or when spawned
void AMathoriaPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMathoriaPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMathoriaPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

