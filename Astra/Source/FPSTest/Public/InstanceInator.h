// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InstanceInator.generated.h"

/**
 *
 */
UCLASS(meta = (ScriptName = "SystemLibrary"))
class FPSTEST_API UInstanceInator : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void check_for_multiple_instances();
};
