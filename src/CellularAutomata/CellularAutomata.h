#ifndef CATEST_H
#define CATEST_H

#include <iostream>
#include "..\Misc\misc.h"

class CellularAutomata {
	int				mSizeX, mSizeY,				// Size of the map
					mBirthLimit, mDeathLimit,	// Limit for a cell to live/die
					mGenerations,				// Number of steps the generation will go on.
					mChanceToStayAlive,			// What is the chance for the cell to stay alive in the beginning?
					mCavesToGenerate,
					mCavesGenerated,
					bogusVariable;
	double			mTimeToGenerate;

	char			**cave, **cave2;

	CellularAutomata() { }

	void			FrameCave();
public:

	static CellularAutomata &GetInstance()
	{
		static CellularAutomata instance;
		return instance;
	}

	CellularAutomata(CellularAutomata const&)		= delete;
	void operator=(CellularAutomata const&)			= delete;

	~CellularAutomata()
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
	inline void		SetChanceToStayAlive(int x)		{ mChanceToStayAlive = x; }
	inline void		SetTimeToGenerate(double x)		{ mTimeToGenerate = x; }
	inline void		SetCavesToGenerate(int x)		{ mCavesToGenerate = x; }
	inline void		SetCavesGenerated(int x)		{ mCavesGenerated = x; }
	// Get functions
	inline int		GetSizeX() const				{ return mSizeX; }
	inline int		GetSizeY() const				{ return mSizeY; }
	inline int		GetBirthLimit() const			{ return mBirthLimit; }
	inline int		GetDeathLimit() const			{ return mDeathLimit; }
	inline int		GetGenerations() const			{ return mGenerations; }
	inline int		GetChanceToStayAlive() const	{ return mChanceToStayAlive; }
	inline int		GetCavesToGenerate() const		{ return mCavesToGenerate; }
	inline int		GetCavesGenerated() const		{ return mCavesGenerated; }
	inline double	GetTimeToGenerate() const		{ return mTimeToGenerate; }
	inline char**	GetCave() const					{ return cave; }

	int				CountLivingNeighbours(int x, int y);

	void			Init(int sizeX = 20, int sizeY = 20, 
						 int birthLimit = 4, int deathLimit = 3, 
						 int generations = 2, int changeToStayAlive = 40,
						 int numOfCavesToGenerate = 1, unsigned int seed = 1);

	void			PrintCave();
	void			RandomizeCave();
	void			EmptyCave();

	void			StepInGeneration();
	void			GenerateCave();
	void			SaveCave();
	void			LifeCycle();
};

#endif