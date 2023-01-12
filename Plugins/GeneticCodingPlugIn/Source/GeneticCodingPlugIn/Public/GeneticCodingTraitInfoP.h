// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneticCodingTraitInfoP.generated.h"

/**
 * 
 */

USTRUCT(immutable, noexport, BlueprintType)
struct GENETICCODINGPLUGIN_API FGeneticCodingTraitInfoP
{


	UPROPERTY(EditAnywhere)
		FString TraitsName;

	UPROPERTY(EditAnywhere)
		bool IsDominateTraitOne;

	UPROPERTY(EditAnywhere)
		bool IsDominateTraitTwo;

	UPROPERTY(EditAnywhere)
		float DominateTraitValue = 0;

	UPROPERTY(EditAnywhere)
		float ResessiveTraitValue = 0;

	float GetValue() {
		if (IsDominateTraitOne || IsDominateTraitTwo)
			return DominateTraitValue;

		return ResessiveTraitValue;
	}

	bool IsDominant() {
		return IsDominateTraitOne || IsDominateTraitTwo;
	}

};
