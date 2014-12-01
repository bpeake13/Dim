// Fill out your copyright notice in the Description page of Project Settings.

#include "Dim.h"
#include "BlockInfo.h"

BlockInfo::BlockInfo(MazeSectionInfo* section, int x, int y)
{
	this->x = x;
	this->y = y;
	this->section = section;

	bIsSolid = true;
}

BlockInfo* BlockInfo::GetOffset(GridAddress& offset)
{
	GridAddress location = GridAddress(x + offset.x, y + offset.y);

	return section->getBlock(location);
}

bool BlockInfo::IsSolid()
{
	return bIsSolid;
}

bool BlockInfo::IsEdge()
{
	return x <= 0 || y <= 0 || x >= section->getWidth() || y >= section->getHeight();
}

bool BlockInfo::IsRemoveable()
{
	int adjCount = 0;

	if (!GetAdjacent(EGridDirection::GD_UP)->bIsSolid)
		adjCount++;

	if (!GetAdjacent(EGridDirection::GD_RIGHT)->bIsSolid)
		adjCount++;

	if (adjCount == 2)
		return false;

	if (!GetAdjacent(EGridDirection::GD_DOWN)->bIsSolid)
		adjCount++;

	if (adjCount >= 2)
		return false;

	if (adjCount == 1 && !GetAdjacent(EGridDirection::GD_LEFT)->bIsSolid)
		return false;

	return true;
}

BlockInfo* BlockInfo::GetAdjacent(EGridDirection::Type direction)
{
	switch (direction)
	{
	case EGridDirection::GD_UP:
		return GetOffset(GridAddress(0, -1));
	case EGridDirection::GD_RIGHT:
		return GetOffset(GridAddress(1, 0));
	case EGridDirection::GD_DOWN:
		return GetOffset(GridAddress(0, -1));
	case EGridDirection::GD_LEFT:
		return GetOffset(GridAddress(-1, 0));
	default:
		return this;
	}
}

void BlockInfo::Generate(FRandomStream* randStream)
{
	bIsSolid = false;

	bool needsGeneration = true;
	int genTryCount = 0;

	do 
	{
		//get a random direction
		int direction = randStream->RandRange(0, 3);
		EGridDirection::Type gridDirection;

		switch (direction)
		{
		case 0:
			gridDirection = EGridDirection::GD_UP;
			break;
		case 1:
			gridDirection = EGridDirection::GD_RIGHT;
			break;
		case 2:
			gridDirection = EGridDirection::GD_DOWN;
			break;
		case 3:
			gridDirection = EGridDirection::GD_LEFT;
			break
		}

		BlockInfo* randBlock = GetAdjacent(gridDirection);//get a block in a random direction

		if (!randBlock || !randBlock->IsRemoveable() || randBlock->IsEdge())//check if that block is removeable
		{
			genTryCount++;
			continue;
		}

		randBlock->Generate(randStream);

		genTryCount++;
	} 
	while (needsGeneration && genTryCount < 4);
}

void BlockInfo::GenerateHallway(FRandomStream* randStream)
{
	bool canRemove = IsRemoveable();

	bIsSolid = false;

	if (!canRemove)
		return;

	bool needsGeneration = true;

	do
	{
		//get a random direction
		int direction = randStream->RandRange(0, 3);
		EGridDirection::Type gridDirection;

		switch (direction)
		{
		case 0:
			gridDirection = EGridDirection::GD_UP;
			break;
		case 1:
			gridDirection = EGridDirection::GD_RIGHT;
			break;
		case 2:
			gridDirection = EGridDirection::GD_DOWN;
			break;
		case 3:
			gridDirection = EGridDirection::GD_LEFT;
			break
		}

		BlockInfo* randBlock = GetAdjacent(gridDirection);//get a block in a random direction

		if (!randBlock || randBlock->IsEdge())//check if that block is removeable
		{
			continue;
		}

		randBlock->GenerateHallway(randStream);

		needsGeneration = false;
	} while (needsGeneration);
}