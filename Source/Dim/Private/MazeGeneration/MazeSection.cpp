// Fill out your copyright notice in the Description page of Project Settings.

#include "Dim.h"
#include "MazeSection.h"

TMap<GridAddress, AMazeSection*> AMazeSection::sectionMap = TMap < GridAddress, AMazeSection* > ;

bool AMazeSection::IsValid(GridAddress& address)
{
	return sectionMap.Contains(address);
}

AMazeSection::AMazeSection(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	BlockTemplate = NULL;
	NavBounds = NULL;

	generator = NULL;
}

void AMazeSection::BeginPlay()
{
	generator = new MazeSectionInfo(Width, Height);
}

void AMazeSection::EndPlay()
{
	sectionMap.Remove(address);
}

void AMazeSection::SetAddress(GridAddress& address)
{
	if (location.bValid)
		return;

	location = address;
	sectionMap.Add(location, this);
}

void AMazeSection::Generate(bool regenerateNavMesh /* = true */)
{
	if (!NavBounds || !BlockTemplate || !location.bValid)//if no nav bounds, fail generation
		return;

	AActor* defaultBlock = BlockTemplate->GetDefaultObject<AActor>();

	FVector boundsOrigin, boundsExtent;
	defaultBlock->GetActorBounds(true, boundsOrigin, boundsExtent);

	FVector gridHalfSize = boundsExtent * FVector(Width, Height, 0);//calculate the size of the bounds

	FVector offset = gridHalfSize * FVector(location.x, location.y, 0);//the offset to place ourselves

	SetActorLocation(offset);//move to the offset

	
	UWorld* world = GetWorld();//get the world

	//create other grid sections if needed
	GridAddress topAddress = GridAddress(location.x, location.y + 1);
	GridAddress rightAddress = GridAddress(location.x + 1, location.y);
	GridAddress bottomAddress = GridAddress(location.x, location.y - 1);
	GridAddress leftAddress = GridAddress(location.x - 1, location.y);

	if (!IsValid(topAddress))
	{
		AMazeSection* top = world->SpawnActor<AMazeSection>();
		top->SetAddress(topAddress);
	}

	if (!IsValid(rightAddress))
	{
		AMazeSection* right = world->SpawnActor<AMazeSection>();
		right->SetAddress(rightAddress);
	}

	if (!IsValid(bottomAddress))
	{
		AMazeSection* bottom = world->SpawnActor<AMazeSection>();
		bottom->SetAddress(bottomAddress);
	}

	if (!IsValid(leftAddress))
	{
		AMazeSection* left = world->SpawnActor<AMazeSection>();
		left->SetAddress(leftAddress);
	}
}