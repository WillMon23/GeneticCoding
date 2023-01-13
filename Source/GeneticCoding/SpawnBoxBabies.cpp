// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBoxBabies.h"
void USpawnBoxBabies::BeginPlay()
{
	AddToGenePool("Name", true, false, 100.0f, 0.5f);
}
