#include "DLA.h"
#include <random>
#include <ctime>
#include <iostream>
#include "../Misc/misc.h"
Builder::Builder(int sx, int sy, int px, int py) 
{
	mStart = new int[2];
	mStart[0] = sx;
	mStart[1] = sy;

	mPos = new int[2];
	mPos[0] = px;
	mPos[1] = py;

	mDirection = 0;
	mCorridorLenght = 5;
	mOrthogonallMovementAllowed = false;
}

Builder::~Builder()
{
	delete mPos;
	delete mStart;
}

//////////////////////////////////////////////////////////////////////////////////////////////

 DLA::~DLA() 
{
	FlushBuilders();
}

 void DLA::FlushBuilders()
 {
	 // Delete all the builders!
	 for (unsigned int i = 0; i < mBuilders.size(); i++)
		 delete mBuilders[i];
 }

void DLA::Init(int sizeX, int sizeY)
{
	// For startpos randomization, and movement randomization.
	std::srand((unsigned int)time(NULL));

	SetSizeX(sizeX);
	SetSizeY(sizeY);
	SetAmountOfBuilders(0);

	// Allocate memory for the map. //////////////
	cave = new char*[GetSizeY()];
	for (int y = 0; y < GetSizeY(); y++)
		cave[y] = new char[GetSizeX()];
}

void DLA::SpawnBuilder(int amountToSpawn) 
{
	for (int i = 0; i < amountToSpawn; i++)
	{
		mBuilders.push_back(new Builder());
		SetAmountOfBuilders(GetAmountOfBuilders() + 1);
	}

	// Randomize the startposition for the builder.
	// It will should never spawn in the "frame" of the cave.
	for (int i = 0; i < amountToSpawn; i++) 
	{
		int xr = 1 + std::rand() % (GetSizeX() - 1),
			yr = 1 + std::rand() % (GetSizeY() - 1);
		if (xr == 0 || xr == GetSizeX() || yr == 0 || yr == GetSizeY()) 
		{
			std::cout << "Illegal coordinates, will exit! ("<< xr << ", " << yr << ")\n";
			FlushBuilders();
			std::cin.get();
			exit(0);
		}
		mBuilders[i]->SetPosXY(xr, yr);
	}
}

void DLA::StepInGeneration()
{
	for (int i = 0; i < GetAmountOfBuilders(); i++)
		std::cout << "(x, y) = ("<< mBuilders[i]->GetPosX() << ", " << mBuilders[i]->GetPosY() << ")\n";
}

void DLA::GenerateCave() 
{
	Timer t;
	t.StartTimer();
	t.StopTimer();
}

void DLA::FrameCave()
{
	for (int i = 0; i < GetSizeY(); i++)
		cave[i][0] = cave[i][GetSizeX() - 1] = '#';

	for (int i = 0; i < GetSizeX(); i++)
		cave[0][i] = cave[GetSizeY() - 1][i] = '#';
}