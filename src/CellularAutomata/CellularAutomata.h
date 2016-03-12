#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include <ctime>
#include <random>

#define WALL 1
#define FLOOR 0

// TODO(Kim): Fix better documentation
typedef struct 
{
							// How many neighbours must be walls?
	int						WallNeighbours1,	// WallNeighbouts1 >= input
							WallNeighbours2;	// WallNeighbouts2 <= input

							// How many generations will we generated?
	int						RepeatSimXGenerations;
} GenerationParameters;

class CellularAutomata
{
							CellularAutomata() { }
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
	/*CellularAutomata(int wallneighbours1, int wallneighbours2,
					 int sizeX, int sizeY, 
					 int fillProbability) {	}*/
	static CellularAutomata &GetInstance() {
		static CellularAutomata instance;
		return instance;
	}
	CellularAutomata(CellularAutomata const&)	= delete;
	void operator=(CellularAutomata const&)		= delete;

	~CellularAutomata();

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
	inline int				GetWallNeighbours1() const { return mGenParams->WallNeighbours1; }
	inline int				GetWallNeighbours2() const { return mGenParams->WallNeighbours2; }

	// TODO(Kim): Implement Set-functions.
	void					SetWallNeighbours1(int x) { mGenParams->WallNeighbours1 = x; }
	void					SetWallNeighbours2(int x) { mGenParams->WallNeighbours2 = x; }
	void					SetXSize(int x) { mSizeX = x; }
	void					SetYSize(int x) { mSizeY = x; }
	void					SetFillProbablity(int x = 50) { mFillProbability = x; }
	// Init the array, and randomize each element in the array.
	// Also sets a wall around the maze.
	void					Init(int wallneighbours1, int wallneighbours2,
								 int sizeX, int sizeY,
								 int fillProbability);

	void					Generate();
};

#endif
