// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
namespace EGridDirection
{
	enum Type
	{
		GD_UP UMETA(DisplayName = "Up"),
		GD_RIGHT UMETA(DisplayName = "Right"),
		GD_DOWN UMETA(DisplayName = "Down"),
		GD_LEFT UMETA(DisplayName = "Left")
	};
}