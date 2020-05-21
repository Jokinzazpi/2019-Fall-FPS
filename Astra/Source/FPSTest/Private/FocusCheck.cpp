// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusCheck.h"
#include "Engine/World.h"
#include "UnrealClient.h"
#include "Engine/GameViewportClient.h"

FocusCheck::FocusCheck()
{
}

FocusCheck::~FocusCheck()
{
}

bool FocusCheck::IsOutOfFocus(APlayerController * player)
{
	//ULocalPlayer * LocPlayer = Cast<ULocalPlayer>(this);
	//
	//if (!LocPlayer->ViewportClient->Viewport || !LocPlayer->ViewportClient->Viewport->IsForegroundWindow())
	//{
	//	// viewport is either not present or not in the foreground.
	//}

	if (player->GetWorld())
	{
		UGameViewportClient * vpClient = player->GetWorld()->GetGameViewport();

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