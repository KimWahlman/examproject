#ifndef CATEST_H
#define CATEST_H

#include <iostream>

class CATest {
	int				mSizeX, mSizeY,				// Size of the map
					mBirthLimit, mDeathLimit,	// Limit for a cell to live/die
					mGenerations,				// Number of steps the generation will go on.
					mChanceToStayAlive;			// What is the chance for the cell to stay alive in the beginning?
	
	char			**cave, **cave2;

	CATest() { }
public:

	static CATest &GetInstance() 
	{
		static CATest instance;
		return instance;
	}

	CATest(CATest const&)							= delete;
	void operator=(CATest const&)					= delete;

	~CATest() 
	{
		//for (int i = 0; i < GetSizeY(); i++) {
		//	delete cave[i];
		//	delete cave2[i];
		//}
		//delete cave;
		//delete cave2;
	} 

	// Set functions
	inline void		SetSizeX(int x)					{ mSizeX = x; }
	inline void		SetSizeY(int y)					{ mSizeY = y; }
	inline void		SetBirthLimit(int x)			{ mBirthLimit = x; }
	inline void		SetDeathLimit(int x)			{ mDeathLimit = x; }
	inline void		SetGenerations(int x)			{ mGenerations = x; }
	inline void		SetChanceToStayAlive(int x)	{ mChanceToStayAlive = x; }
	// Get functions
	inline int		GetSizeX() const				{ return mSizeX; }
	inline int		GetSizeY() const				{ return mSizeY; }
	inline int		GetBirthLimit() const			{ return mBirthLimit; }
	inline int		GetDeathLimit() const			{ return mDeathLimit; }
	inline int		GetGenerations() const			{ return mGenerations; }
	inline int		GetChanceToStayAlive() const	{ return mChanceToStayAlive; }

	int				CountLivingNeighbours(int x, int y);

	void			Init(int sizeX = 20, int sizeY = 20, 
						 int birthLimit = 4, int deathLimit = 3, 
						 int generations = 2, int changeToStayAlive = 40, 
						 unsigned int seed = 0);

	void			PrintCave();
	void			RandomizeCave();
	void			EmptyCave();
	void			FrameCave();

	void			StepInGeneration();
	void			GenerateCave();
	
};

#endif