// Fill out your copyright notice in the Description page of Project Settings.


#include "Wave_System.h"

// Sets default values
AWave_System::AWave_System()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWave_System::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWave_System::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWave_System::set_spawn_points_vec(TArray<AActor*> &spawns)
{
	m_spawn_points = spawns;
}

