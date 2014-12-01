// Fill out your copyright notice in the Description page of Project Settings.

#include "Dim.h"
#include "MazeSectionInfo.h"

EGridDirection::Type getOpposite(EGridDirection::Type direction)
{
	switch (direction)
	{
	case EGridDirection::GD_UP:
		return EGridDirection::GD_DOWN;
	case EGridDirection::GD_RIGHT:
		return EGridDirection::GD_LEFT;
	case EGridDirection::GD_DOWN:
		return EGridDirection::GD_UP;
	case EGridDirection::GD_LEFT:
		return EGridDirection::GD_RIGHT;
	}

	return direction;
}

MazeSectionInfo::MazeSectionInfo(int width, int height)
{
	this->width = width;
	this->height = height;

	grid = new BlockInfo*[width * height];//generate the block buffer for the grid

	//Generate blocks
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int i = y * width + x;
			grid[i] = new BlockInfo(this, x, y);//create the new block
		}
	}
}

MazeSectionInfo::~MazeSectionInfo()
{
	int length = width * height;//get the length of the buffer
	for (int i = 0; i < length; i++)
	{
		delete (grid[i]);
	}

	delete grid;
}

int MazeSectionInfo::getWidth() const
{
	return width;
}

int MazeSectionInfo::getHeight() const
{
	return height;
}

BlockInfo* MazeSectionInfo::getBlock(GridAddress& location)
{
	if (!location.bValid)
		return NULL;

	int address = location.y * width + location.x;
	int length = width * height;

	if (address < 0 || address >= length)
		return NULL;

	return grid[address];
}

BlockInfo* MazeSectionInfo::getEntrence(EGridDirection::Type edge)
{
	int offset = (int)edge;
	GridAddress address = entrences[offset];

	if (!address.bValid)
		return NULL;

	return getBlock(address);
}

GridAddress MazeSectionInfo::convertToLocal(GridAddress& original, EGridDirection::Type sharingEdge)
{
	switch (sharingEdge)
	{
	case EGridDirection::GD_UP:
		return GridAddress(original.x, original.y - height);
	case EGridDirection::GD_RIGHT:
		return GridAddress(original.x + width, original.y);
	case EGridDirection::GD_DOWN:
		return GridAddress(original.x, original.y + height);
	case EGridDirection::GD_LEFT:
		return GridAddress(original.x - width, original.y);
	}

	return GridAddress(0, 0, false);
}

GridAddress MazeSectionInfo::getEdgeAddress(GridAddress& address)
{
	int halfWidth = width / 2;
	int halfHeight = height / 2;

	GridAddress edgeAddress = GridAddress(0, 0);
	edgeAddress.x = address.x < halfWidth ? 0 : width - 1;
	edgeAddress.y = address.y < halfHeight ? 0 : height - 1;

	return edgeAddress;
}

void MazeSectionInfo::generate(FRandomStream* randStream)
{
	int x = randStream->RandRange(1, width - 2);
	int y = randStream->RandRange(1, height - 2);

	GridAddress blockAddress = GridAddress(x, y);

	BlockInfo* startBlock = getBlock(blockAddress);
	startBlock->Generate(randStream);
}

void MazeSectionInfo::generateWall(FRandomStream* randStream, MazeSectionInfo* adjacent, EGridDirection::Type wallDirection)
{
	GridAddress entranceStart;

	if (adjacent)
	{
		EGridDirection opposite = getOpposite(wallDirection);
		entranceStart = adjacent->getEntrence(opposite);
	}
	else
	{

	}
}