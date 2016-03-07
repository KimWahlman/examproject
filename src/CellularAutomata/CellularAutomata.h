#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include <ctime>
#include <random>

#define WALL 1
#define FLOOR 0

// TODO: Fix better documentation
typedef struct 
{
							// How many neighbours must be walls?
	int						WallNeighbours1,
							WallNeighbours2;

							// How many generations will we generated?
	int						RepeatSimXGenerations;
} GenerationParameters;

class CellularAutomata
{
							// How probible is it that a cell is a wall?
	int						mFillProbability;
							// Size of the map.
	int						mSizeX, mSizeY;
	int						mGenerations;				

	GenerationParameters	*mGenParams,
							*mGenParamsSet;

	int						**mGrid,
							**mGrid2;
public:
	CellularAutomata(int i, int j, 
					 int sizeX, int sizeY, 
					 int fillProbability) {	}

	~CellularAutomata() { }

	inline void				SetGenParams(int i, int j)		
							{ mGenParams->WallNeighbours1 = i; mGenParams->WallNeighbours2 = j; }

	inline void				SetGenParamsSet(int i, int j)	
							{ mGenParamsSet->WallNeighbours1 = i, mGenParamsSet->WallNeighbours2 = j; }
	
	// Randomize if a tile is open or not in the cave.
	// This is based upon probability. Higher value is equal to
	// a higher chance the space is a wall.
	inline int				RandomizeCells() { return (std::rand() % 100 < mFillProbability ? WALL : FLOOR); }

	// Some GetFunctions that might come in handy.
	inline int				GetSizeX() const { return mSizeX; }
	inline int				GetSizeY() const { return mSizeY; }
	inline int				GetFillProbability() const { return mFillProbability; }

	// TODO: Implement Set-functions.

	// Init the array, and randomize each element in the array.
	// Also sets a wall around the maze.
	void					init();
};

#endif
