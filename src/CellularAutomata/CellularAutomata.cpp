#include "CellularAutomata.h"

//CellularAutomata::CellularAutomata(int wallneighbours1, int wallneighbours2, int sizeX, int sizeY, int fillProbability)
//{
//	mGenParams->WallNeighbours1 = wallneighbours1;
//	mGenParams->WallNeighbours2 = wallneighbours2;
//	mFillProbability = fillProbability;
//	mSizeX = sizeX;
//	mSizeY = sizeY;
//}

//TODO(Kim): Implement deletion of pointers.
CellularAutomata::~CellularAutomata() 
{ 
	delete mGenParams;
	delete mGenParamsSet;

	// TODO(Kim): Delete pointers for everything
	for (int y = 0; y < GetSizeY(); y++)
		delete mGrid[y];
	for (int y = 0; y < GetSizeY(); y++)
		delete mGrid2[y];
}

void CellularAutomata::Init(int wallneighbours1, int wallneighbours2, int sizeX, int sizeY, int fillProbability)
{ 
	mGenParams = mGenParamsSet = new GenerationParameters;

	SetWallNeighbours1(wallneighbours1);
	SetWallNeighbours2(wallneighbours2);
	SetXSize(sizeX);
	SetYSize(sizeY);
	SetFillProbablity(fillProbability);

	mGrid = new int*[GetSizeY()];
	mGrid2 = new int*[GetSizeX()];

	// Allocate memory for the two grids.
	// This will make the array an 2D array.
	// Each 'i', could be visualized as the Y-axis.
	for (int i = 0; i < GetSizeY(); i++)
	{
		mGrid[i] = new int[GetSizeX()];
		mGrid2[i] = new int[GetSizeX()];
	}

	// Randomize if the element is a wall or floor.
	for (int y = 1; y < GetSizeY() - 1; y++)
		for (int x = 1; x < GetSizeX() - 1; x++)
			mGrid[y][x] = RandomizeCells();

	// All elements in mGrid2 is set to be a wall.
	for (int y = 0; y < GetSizeY(); y++)
		for (int x = 0; x < GetSizeX(); x++)
			mGrid2[y][x] = WALL;

	// Set the outer rows and columns to be a wall.
	for (int y = 0; y < GetSizeX(); y++)
		mGrid[y][0] = mGrid[y][GetSizeY() - 1] = WALL;
	for (int x = 0; x < GetSizeX(); x++)
		mGrid[0][x] = mGrid[GetSizeX() - 1][x] = WALL;
}

void CellularAutomata::Generate() {
	for (int y = 1; y < GetSizeY() - 1; y++)
	{
		for (int x = 1; x < GetSizeX() - 1; x++)
		{
			int AdjustCountWallNeigbour1 = 0,
				AdjustCountWallNeigbour2 = 0;

			// This will help adjust if a tile will be a floor tile or a wall tile
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					if (mGrid[y + i][x + j] != FLOOR)
						AdjustCountWallNeigbour1++;

			//for()
		}
	}
}
