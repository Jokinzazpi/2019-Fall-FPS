// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerController.h"
#include "Engine/World.h"
#include "UnrealClient.h"
#include "Engine/GameViewportClient.h"

bool AFPlayerController::check_for_out_of_focus()
{
	//ULocalPlayer * LocPlayer = Cast<ULocalPlayer>(this);
	//
	//if (!LocPlayer->ViewportClient->Viewport || !LocPlayer->ViewportClient->Viewport->IsForegroundWindow())
	//{
	//	// viewport is either not present or not in the foreground.
	//}

	if (GetWorld())
	{
		UGameViewportClient * vpClient = GetWorld()->GetGameViewport();

		if (vpClient)
		{
			FViewport * vp = vpClient->Viewport;

			if (vp)
			{
				return vp->IsForegroundWindow();
			}
		}
	}

	return false;
}



