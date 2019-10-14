// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wave_System.generated.h"

UCLASS()
class FPSTEST_API AWave_System : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWave_System();

	UFUNCTION(BlueprintCallable, Category = "Set spawn points")
		void set_spawn_points_vec(TArray<AActor *> &spawns);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//vector of all spawn points in the map
	TArray<AActor *> m_spawn_points;

};
