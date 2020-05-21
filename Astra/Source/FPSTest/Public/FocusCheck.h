// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

/**
 * 
 */
class FPSTEST_API FocusCheck : public UObject
{
public:
	FocusCheck();
	~FocusCheck();

	UFUNCTION(BlueprintCallable)
		static bool IsOutOfFocus(APlayerController * player);
};
