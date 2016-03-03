#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include <ctime>
#include <random>

#define WALL 1
#define FLOOR 0

// TODO: Fix better documentation
typedef struct 
{
	
	int						WallNeighbours1,			// How many neighbours must be walls?
							WallNeighbours2;

	int						RepeatSimXTurns;			// How many generations will we generated?
} GenerationParameters;

class CellularAutomata
{
	int						mFillProbability;			// How probible is it that a cell is a wall?
	int						mSizeX, mSizeY;				// Size of the map.
	int						mGenerations;				

	GenerationParameters	*mGenParams,
							*mGenParamsSet;

	int						**mGrid,
							**mGrid2;
public:
	CellularAutomata(int i, int j, int sizeX, int sizeY, int fillProbability) 
	{
		mGenParams->WallNeighbours1 = i; 
		mGenParams->WallNeighbours2 = j;
		mFillProbability			= fillProbability;
		mSizeX						= sizeX;
		mSizeY						= sizeY;

	}

	~CellularAutomata() { }

	inline void				SetGenParams(int i, int j)		
							{ mGenParams->WallNeighbours1 = i; mGenParams->WallNeighbours2 = j; }

	inline void				SetGenParamsSet(int i, int j)	
							{ mGenParamsSet->WallNeighbours1 = i, mGenParamsSet->WallNeighbours2 = j; }
	
	// Randomize if a tile is open or not in the cave.
	inline int				RandomizeCells() { return (std::rand() % 100 < mFillProbability ? WALL : FLOOR); }

	// TODO: This function will be used to init the array, and randomize each element in the array
	inline void				init() 
	{

	}
};

#endif
