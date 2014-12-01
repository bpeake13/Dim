// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MazeSection.generated.h"
#include "NavMeshBoundsVolume.h"

/**
 * 
 */
UCLASS()
class DIM_API AMazeSection : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	/*Generates the maze section for this*/
	UFUNCTION(BlueprintCallable)
	void Generate(bool regenerateNavMesh = true);

protected:

	void BeginPlay() override;

	void EndPlay() override;

	void SetAddress(GridAddress& address);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generation")
	TSubobjectPtr<class UBoxComponent> ActiveArea;

	UPROPERTY(EditInstanceOnly, Category = "Navigation")
	ANavMeshBoundsVolume* NavBounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generation")
	TSubclassOf<class AActor> BlockTemplate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generation")
	int Width;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generation")
	int Height;

private:

	static bool IsValid(GridAddress& address);

	GridAddress location;

	MazeSectionInfo* generator;

	static TMap<GridAddress, AMazeSection*> sectionMap;
};
