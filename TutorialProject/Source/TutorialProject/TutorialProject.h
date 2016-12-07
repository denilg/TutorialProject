// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

UENUM(BlueprintType)
enum class EStencilColour : uint8
{
	SC_Green = 250 UMETA(DisplayName = "Green"),
	SC_Blue = 251 UMETA(DisplayName = "Blue"),
	SC_Red = 252 UMETA(DisplayName = "Red"),
	SC_White = 253 UMETA(DisplayName = "White"),
};