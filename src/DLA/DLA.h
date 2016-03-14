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
	int*					mStart;			// Where will the builder spawn?
	int*					mPos;				// Where is the builder?
	int						mDirection,			// What direction will the builder move in? (Randomized)
							mCorridorLenght;	// How long can a corridor be, might move this to the DLA class.

	bool					mOrthogonallMovementAllowed; // Is orthogonal movement allowed? If it isn't carve a wider cooridor on the diagonal.	
public:
	Builder();
	~Builder() { delete mStart; }

	inline void				SetStartPos(int x, int y) { mStart[0] = x, mStart[1] = y; }
	inline void				SetXY(int x, int y) { mPos[0] = x; mPos[1] = y; }
	inline void				SetX(int x) { mPos[0] = x; }
	inline void				SetY(int y) { mPos[1] = y; }
	inline void				SetDirection(int dir) { mDirection = dir; }
	inline void				SetCorridorLenght(int x) { mCorridorLenght = x; }
	inline void				SetOrthogonallMovementAllowed(bool x) { mOrthogonallMovementAllowed = x; }

	inline int*				GetStart() const { return mStart; }
	inline int				GetStartX() const { return mStart[0]; }
	inline int				GetStartY() const { return mStart[1]; }

	inline int*				GetPos() const { return mPos; }
	inline int				GetPosX() const { return mPos[0]; }
	inline int				GetPosY() const { return mPos[1]; }
};


class DLA
{
	int						mSizeX, mSizeY,			// Map size
							mBuildersToSpawn,
							mSpawnedBuilders;
	char**					map;
	std::vector<Builder>	mBuilders;				// Container for builders.
	DLA() { }
	
public:
	static DLA				&GetInstance()
	{
		static DLA instance;
		return instance;
	}

							DLA(DLA const&)			= delete;
	void					operator=(DLA const&)	= delete;

	// TODO(Kim): Implement this!
	void					Init(int sizeX, int sizeY, int buildersToSpawn);
	void					SpawnBuilder();
	// Might need these.
	void					StepInGeneration();
	void					GenerateCave();

	// Setters
	inline void				SetAmountOfBuilders(int x) { mSpawnedBuilders = x; }
	inline void				SetStartPos(int x, int y, int builder) { mBuilders[builder].SetStartPos(x, y); }
	// Getters
	inline int				GetAmountOfBuilders() const { return mSpawnedBuilders; }

};

#endif