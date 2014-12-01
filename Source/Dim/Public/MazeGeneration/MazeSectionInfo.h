// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BlockInfo.h"
#include "EGridDirection.h"

class BlockInfo;

/*Represents a grid location*/
USTRUCT()
struct GridAddress
{
	int x;
	int y;
	bool bValid;

	GridAddress(int x, int y, bool bValid)
	{
		this->x = x;
		this->y = y;
		this->bValid = bValid;
	}

	GridAddress(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->bValid = true;
	}
};

/**
 * 
 */
class DIM_API MazeSectionInfo
{
public:
	MazeSectionInfo(int width, int height);
	~MazeSectionInfo();

	int getWidth() const;

	int getHeight() const;

	BlockInfo* getBlock(GridAddress& location);

	BlockInfo* getEntrence(EGridDirection::Type edge);

	/*Converts a grid from another grid into a local address*/
	GridAddress convertToLocal(GridAddress& original, EGridDirection::Type sharingEdge);

	GridAddress getEdgeAddress(GridAddress& address);

	void generate(FRandomStream* randStream);

	void generateWall(FRandomStream* randStream, MazeSectionInfo* adjacent, EGridDirection::Type wallDirection);
private:
	int width;
	int height;

	GridAddress entrences[4];//all entrences into this section

	BlockInfo** grid;//the grid of blocks
};
