// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyTestObject.generated.h"

/**
 * 
 */
UCLASS()
class GARBAGECOLLECTORTEST_API UMyTestObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 MyTestValue;
};
