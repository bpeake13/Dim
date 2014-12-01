// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MazeSectionInfo.h"

class MazeSectionInfo;

/**
 * Contains info on a specified block
 */
class DIM_API BlockInfo
{
public:
	BlockInfo(MazeSectionInfo* section, int x, int y);

	/*Checks to see if this block is solid*/
	bool IsSolid();

	bool IsEdge();

	bool IsRemoveable();

	BlockInfo* GetAdjacent(EGridDirection::Type direction);

	/*Gets a block at an offset from this block*/
	BlockInfo* GetOffset(GridAddress& offset);

	void Generate(FRandomStream* randStream);

	void GenerateHallway(FRandomStream* randStream);

private:
	bool bIsSolid;

	int x;
	int y;

	MazeSectionInfo* section;
};
