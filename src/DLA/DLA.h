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

struct Builder {
	int			startX, startY,	// Where will the builder spawn?
				x, y,			// Where is the builder?
				direction,		// What direction will the builder move in? (Randomized)
				mCorridorLenght;// How long can a corridor be, might move this to the DLA class.

	bool		mOrthogonallMovementAllowed; // Is orthogonal movement allowed? If it isn't carve a wider cooridor on the diagonal.
		
};


class DLA
{
	int				mSizeX, mSizeY,			// Map size
					mBuildersToSpawn,
					mSpawnedBuilders;
	char** map;
	std::vector<Builder> mBuilders;			// Container for builders.
	DLA() { }
	
public:
	static DLA &GetInstance()
	{
		static DLA instance;
		return instance;
	}

	DLA(DLA const&) = delete;
	void operator=(DLA const&) = delete;

	void Init(int sizeX, int sizeY, int buildersToSpawn);
	void SpawnBuilder();

	// Setters
	inline void SetAmountOfBuilders(int x) { mSpawnedBuilders = x; }
	// Getters
	inline int GetAmountOfBuilders() const { return mSpawnedBuilders; }

};

#endif