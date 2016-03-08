#include "CellularAutomata.h"

//CellularAutomata::CellularAutomata(int wallneighbours1, int wallneighbours2, int sizeX, int sizeY, int fillProbability)
//{
//	mGenParams->WallNeighbours1 = wallneighbours1;
//	mGenParams->WallNeighbours2 = wallneighbours2;
//	mFillProbability = fillProbability;
//	mSizeX = sizeX;
//	mSizeY = sizeY;
//}

//TODO: Implement deletion of pointers.
CellularAutomata::~CellularAutomata() 
{ 
	delete mGenParams;
	delete mGenParamsSet;
}

void CellularAutomata::init(int wallneighbours1, int wallneighbours2, int sizeX, int sizeY, int fillProbability)
{ 
	mGenParams = mGenParamsSet = new GenerationParameters;

	SetWallNeighbours1(wallneighbours1);
	SetWallNeighbours2(wallneighbours2);
	SetXSize(sizeX);
	SetYSize(sizeY);
	SetFillProbablity(fillProbability);

	mGrid = new int*[mSizeY];
	mGrid2 = new int*[mSizeX];

	// Allocate memory for the two grids.
	// This will make the array an 2D array.
	// Each 'i', could be visualized as the Y-axis.
	for (int i = 0; i < mSizeY; i++)
	{
		mGrid[i] = new int[mSizeX];
		mGrid2[i] = new int[mSizeX];
	}

	// Randomize if the element is a wall or floor.
	for (int i = 1; i < mSizeY - 1; i++)			// Y-axis
		for (int j = 1; j < mSizeX - 1; j++)		// X-axis
			mGrid[i][j] = RandomizeCells();

	// All elements in mGrid2 is set to be a wall.
	for (int i = 0; i < mSizeY; i++)
		for (int j = 0; j < mSizeX; j++)
			mGrid2[i][j] = WALL;

	// Set the outer rows and columns to be a wall.
	for (int i = 0; i < mSizeY; i++)
		mGrid[i][0] = mGrid[i][mSizeX - 1] = WALL;
	for (int i = 0; i < mSizeY; i++)
		mGrid[0][i] = mGrid[mSizeY - 1][i] = WALL;
}
