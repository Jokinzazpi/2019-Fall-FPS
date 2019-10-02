// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunctionLibrary.generated.h"

#include <vector>

UCLASS();
class FPSTEST_API Wave
{
public:
	Wave() = default;
	Wave(unsigned minion, unsigned exp_minion, unsigned grunts, unsigned tanks, unsigned flying);
	~Wave() = default;

	//GETTORS FOR BLUEPRINTS
	UFUNCTION(BlueprintCallable, Category = "Number of minions gettor")
		unsigned get_number_of_minions();
	UFUNCTION(BlueprintCallable, Category = "Number of explosive minions gettor")
		unsigned get_number_of_exp_minions();
	UFUNCTION(BlueprintCallable, Category = "Number of grunts gettor")
		unsigned get_number_of_grunts();
	UFUNCTION(BlueprintCallable, Category = "Number of tanks gettor")
		unsigned get_number_of_tanks();
	UFUNCTION(BlueprintCallable, Category = "Number of flying gettor")
		unsigned get_number_of_flying();

	//SETTORS FOR BLUEPRINTS
	UFUNCTION(BlueprintCallable, Category = "Number of minions settor")
		void set_number_of_minions(unsigned number);
	UFUNCTION(BlueprintCallable, Category = "Number of explosive minions settor")
		void set_number_of_exp_minions(unsigned number);
	UFUNCTION(BlueprintCallable, Category = "Number of grunts settor")
		void set_number_of_grunts(unsigned number);
	UFUNCTION(BlueprintCallable, Category = "Number of tanks settor")
		void set_number_of_tanks(unsigned number);
	UFUNCTION(BlueprintCallable, Category = "Number of flying settor")
		void set_number_of_flying(unsigned number);

//private:
	//unsigned m_number_of_priority_enemies{0};//this is the total
	unsigned m_number_of_minions{0};
	unsigned m_number_of_exp_minions{0};
	unsigned m_number_of_grunts{0};
	unsigned m_number_of_tanks{0};
	unsigned m_number_of_flying{0};
};

/**
 * 
 */
UCLASS();
class FPSTEST_API WaveSystem
{
public:
	WaveSystem();
	~WaveSystem();

	UFUNCTION(BlueprintCallable, Category = "new wave started")
		void new_wave_started();

	UFUNCTION(BlueprintCallable, Category = "check if new wave shoul start")
		bool has_new_wave_started();

	UFUNCTION(BlueprintCallable, Category = "decrement number of minions by one")
		void decrement_number_minions() { m_actual_wave.m_number_of_minions -= 1; }
	UFUNCTION(BlueprintCallable, Category = "decrement number of explosive minions by one")
		void decrement_number_exp_minions() { m_actual_wave.m_number_of_exp_minions -= 1; }
	UFUNCTION(BlueprintCallable, Category = "decrement number of grunts by one")
		void decrement_number_grunts() { m_actual_wave.m_number_of_grunts -= 1; }
	UFUNCTION(BlueprintCallable, Category = "decrement number of tanks by one")
		void decrement_number_tanks() { m_actual_wave.m_number_of_tanks -= 1; }
	UFUNCTION(BlueprintCallable, Category = "decrement number of flying by one")
		void decrement_number_flying() { m_actual_wave.m_number_of_flying -= 1; }

private:
	unsigned m_wave_number{0};
	unsigned m_max_number_of_waves{ 5 };

	std::vector<Wave> m_waves;
	Wave m_actual_wave;
};
