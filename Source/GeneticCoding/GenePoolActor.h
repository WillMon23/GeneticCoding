// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneticCodingActorP.h"
#include "GenePoolActor.generated.h"

/**
 * 
 */
UCLASS()
class GENETICCODING_API AGenePoolActor : public AGeneticCodingActorP
{
	GENERATED_BODY()

		void BeginPlay() override;
	void Tick(float deltaTime) override;
};
