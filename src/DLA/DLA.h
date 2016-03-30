#ifndef DLA_H
#define DLA_H

#include <vector>
//Pseudocode for block aggregation
//* Fill a level with wall
//* Dig a seed tile or block, probably in the centre
//* Do until the level is considered sufficiently full(predefined number of blocks, edge proximity or number of tiles dug) : 
//		* Choose a block, either from a given set or using a function
//		* Choose a location from which to begin the block's walk  
//				* If necessary, limit this choice to locations that don't interfere with already - dug sections
//		* Do until the block neighbours or collides with the dug - out section : 
//				* Move the block one step in a random direction
//		* Dig out the tiles covered by the block
//* Add any other desired features, eg.extra corridors to increase connectivity

// Papers
// Diffusion Limited Aggregation with modified local rules
//		http://arxiv.org/ftp/arxiv/papers/1105/1105.5558.pdf
//		http://www.diva-portal.org/smash/record.jsf?pid=diva2%3A551051&dswid=1222

class Builder {
	int*					mStart;				// Where will the builder spawn?
	int*					mPos;				// Where is the builder?
	int						mDirection,			// What direction will the builder move in? (Randomized)
							mCorridorLenght;	// How long can a corridor be, might move this to the DLA class.
							

	bool					mOrthogonallMovementAllowed,	// Is orthogonal movement allowed? If it isn't carve a wider cooridor on the diagonal.	
							mOutside;						// Is the builder outside the map, then we shall remove it.
public:
	Builder(int sx = 1, int sy = 1, int px = 1, int py = 1);
	~Builder();

	inline void				SetStartPos(int x, int y) { mStart[0] = x, mStart[1] = y; }
	inline void				SetPosXY(int x, int y) { mPos[0] = x; mPos[1] = y; }
	inline void				SetPosX(int x) { mPos[0] = x; }
	inline void				SetPosY(int y) { mPos[1] = y; }
	inline void				SetDirection(int dir) { mDirection = dir; }
	inline void				SetCorridorLenght(int x) { mCorridorLenght = x; }
	inline void				SetOrthogonalMovementAllowed(bool x) { mOrthogonallMovementAllowed = x; }

	inline int*				GetStartPos() const { return mStart; }
	inline int				GetStartX() const { return mStart[0]; }
	inline int				GetStartY() const { return mStart[1]; }
	
	inline int				GetDirection() const { return mDirection; }
	inline int				GetCorridorLenght() const { return mCorridorLenght; }

	inline int*				GetPos() const { return mPos; }
	inline int				GetPosX() const { return mPos[0]; }
	inline int				GetPosY() const { return mPos[1]; }

	inline bool				GetOrtogonalMovementAllowed() const { return mOrthogonallMovementAllowed; }
};


class DLA
{
	int						mSizeX, mSizeY,			// Map size
							mBuildersToSpawn,
							mSpawnedBuilders,
							mAllocatedBlocks,		// How much of the cave has been filled.
							mDigSize,
							mDigged,
							mCavesGenerated,
							mCavesToGenerate,
							mBTemp,
							mBCurr;



	double					mTimeToGenerate;

	bool					mForcedStop;

	char**					cave;
	Builder*				builder;				// 
	std::vector<Builder*>	mBuilders;				// Container for builders.
	std::vector<int[2]>		mOpen;
	Builder					mBuilder;
	DLA() { }

	void					FrameCave();
public:
	~DLA();
	static DLA				&GetInstance()
	{
		static DLA instance;
		return instance;
	}

							DLA(DLA const&)			= delete;
	void					operator=(DLA const&)	= delete;

	void					Init(int sizeX, int sizeY);
	void					LifeCycle();
	void					SpawnBuilder(int amountToSpawn = 1);
	void					EmptyCave();
	void					PrintCave();
	void					StepInGeneration();
	void					GenerateCave();
	void					FlushBuilders();
	void					CountFloorTiles();
	void					SaveCave();
	void					AllocateMemory();
	inline void				IncrementAllocatedBlocks() { mAllocatedBlocks++; }

	// Setters
	inline void				SetSizeX(int x) { mSizeX = x; }
	inline void				SetSizeY(int x) { mSizeY = x; }
	inline void				SetAmountOfBuilders(int x) { mSpawnedBuilders = x; }
	inline void				SetStartPos(int x, int y, int builder) { mBuilders[builder]->SetStartPos(x, y); }
	inline void				SetAllocatedBlocks(int x) { mAllocatedBlocks = x; }
	inline void				SetDigSize(int x) { mDigSize = x; }
	inline void				SetCavesGenerated(int x) { mCavesGenerated = x; }
	inline void				SetCavesToGenerate(int x) { mCavesToGenerate = x; }
	inline void				SetTimeToGenerate(double x) { mTimeToGenerate = x; }
	inline void				SetDigged(int x) { mDigged = 0; }
	inline void				DeleteBuilder(int x) { }

	// Getters
	inline int				GetAmountOfBuilders() const { return mSpawnedBuilders; }
	inline int				GetSizeX() const { return mSizeX; }
	inline int				GetSizeY() const { return mSizeY; }
	inline int				GetAllocatedBlocks() const { return mAllocatedBlocks; }
	inline int				GetDigSize() const { return mDigSize; }
	inline int				GetDigged() const { return mDigged; }
	inline int				GetDirection() const { return mBuilders[0]->GetDirection(); }
	inline int				GetCavesGenerated() const { return mCavesGenerated; }
	inline int				GetCavesToGenerate() const { return mCavesToGenerate; }

	inline double			GetTimeToGenerate() { return mTimeToGenerate; }
	inline char**			GetCave() { return cave; }
};

#endif