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
	mCorridorLenght = 0;
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

 void DLA::EmptyCave()
 {
	 for (int y = 0; y < GetSizeY(); y++)
		 for (int x = 0; x < GetSizeX(); x++)
			 cave[y][x] = '#';
 }

 void DLA::CountFloorTiles()
 {
	 mDigged = 0;
	 for (int i = 0; i < GetSizeY(); i++)
		 for (int j = 0; j < GetSizeX(); j++)
			 if (cave[i][j] == '.')
				 mDigged++;
 }

 void DLA::FlushBuilders()
 {
	 int temp = GetAmountOfBuilders();
	 for (int i = 0; i < temp; i++)
	 {
		 delete mBuilders[i];
		 mBuilders.pop_back();
		 SetAmountOfBuilders(GetAmountOfBuilders() - 1);
	 }
 }

void DLA::Init(int sizeX, int sizeY)
{
	// Do we have a specified seed or will we randomize?
	// Randomize
	std::srand((unsigned int)time(NULL));

	SetSizeX(sizeX);
	SetSizeY(sizeY);
	SetAmountOfBuilders(0);
	SetAllocatedBlocks(0);
	SetDigSize((GetSizeY() * GetSizeX()) / 2);
	// Allocate memory for the map. //////////////
	cave = new char*[GetSizeY()];
	for (int y = 0; y < GetSizeY(); y++)
		cave[y] = new char[GetSizeX()];

	EmptyCave();
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
		int xr = (GetSizeX() - 1) / 2,//1 + std::rand() % (GetSizeX() - 1) ,
			yr = (GetSizeY() - 1) / 2;//1 + std::rand() % (GetSizeY() - 1) ;
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
	//for (int i = 0; i < GetAmountOfBuilders(); i++)
	//	std::cout << "(x, y) = ("<< mBuilders[i]->GetPosX() << ", " << mBuilders[i]->GetPosY() << ")\n";
	if (GetAmountOfBuilders() < 1)
		SpawnBuilder();
	else
	{
		//mBuilders[0]->SetPosXY(GetSizeX(), GetSizeY());
		while (GetAllocatedBlocks() <= GetDigSize())
		{
			//PrintCave();
			//system("cls");
			//std::cout << "Stepping...\n";
			//std::cout << "GetAllocatedBlocks() = " << GetAllocatedBlocks() << ", mDigSize = " << (mDigSize) << "\n";
			//std::cout << "Builders = " << GetAmountOfBuilders() << "\n";
			for (int i = 0; i < GetAmountOfBuilders(); i++)
			{
				mBuilders[i]->SetDirection(std::rand() % 4);
				// Norr Y-led
				if (mBuilders[i]->GetDirection() == 0 && mBuilders[i]->GetPosY() > 0)
				{
					mBuilders[i]->SetPosY(mBuilders[i]->GetPosY() - 1);
					mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
						cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						IncrementAllocatedBlocks();
					}
				}
				// Öst X-led
				else if (mBuilders[i]->GetDirection() == 1 && mBuilders[i]->GetPosX() < GetSizeX())
				{
					mBuilders[i]->SetPosX(mBuilders[i]->GetPosX() + 1);
					mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
						cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						IncrementAllocatedBlocks();
					}
				}
				// Syd Y-led
				else if (mBuilders[i]->GetDirection() == 2 && mBuilders[i]->GetPosY() < GetSizeY())
				{
					mBuilders[i]->SetPosY(mBuilders[i]->GetPosY() + 1);
					mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
						cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						IncrementAllocatedBlocks();
					}
				}
				// Väst X-led
				else if (mBuilders[i]->GetDirection() == 3 && mBuilders[i]->GetPosX() > 0)
				{
					mBuilders[i]->SetPosX(mBuilders[i]->GetPosX() - 1);
					mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
						cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						IncrementAllocatedBlocks();
					}
				}
				// Nordöst X- och Y-led
				if (mBuilders[i]->GetOrtogonalMovementAllowed()) {
					if (mBuilders[i]->GetDirection() == 4 && mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() > 0)
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() + 1, mBuilders[i]->GetPosY() - 1);
						mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							IncrementAllocatedBlocks();
						}
					}
					// Sydöst X- och Y-led
					else if (mBuilders[i]->GetDirection() == 5 && mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY())
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() + 1, mBuilders[i]->GetPosY() + 1);
						mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							IncrementAllocatedBlocks();
						}
					}
					// Sydväst X- och Y-led
					else if (mBuilders[i]->GetDirection() == 6 && mBuilders[i]->GetPosX() > 0 && mBuilders[i]->GetPosY() < GetSizeY())
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() - 1, mBuilders[i]->GetPosY() + 1);
						mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							IncrementAllocatedBlocks();
						}
					}
					// Nordväst X- och Y-led
					else if (mBuilders[i]->GetDirection() == 7 && mBuilders[i]->GetPosX() > 0 && mBuilders[i]->GetPosY() > 0)
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() - 1, mBuilders[i]->GetPosY() - 1);
						mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							IncrementAllocatedBlocks();
						}
					}
				}
				// Ensure that builder is touching an existing spot
				if ((mBuilders[i]->GetPosX() < (GetSizeX() - 1) && mBuilders[i]->GetPosY() < (GetSizeY() - 1) &&
					mBuilders[i]->GetPosX() > 1 && mBuilders[i]->GetPosY() > 1) && mBuilders[i]->GetCorridorLenght() <= GetDigSize());
				else 
					{ FlushBuilders();	SpawnBuilder();	}
			}
		}
	}
}

void DLA::GenerateCave() 
{
	Timer t;
	t.StartTimer();
	DLA::GetInstance().StepInGeneration();
	t.StopTimer();
	SetTimeToGenerate(t.GetDuration());
	//std::cout << "Time to generate: " << GetTimeToGenerate() << "ms\n";
}

void DLA::FrameCave()
{
	for (int i = 0; i < GetSizeY(); i++)
		cave[i][0] = cave[i][GetSizeX() - 1] = '#';

	for (int i = 0; i < GetSizeX(); i++)
		cave[0][i] = cave[GetSizeY() - 1][i] = '#';
}

void DLA::PrintCave()
{
	FrameCave();
	for (int y = 0; y < GetSizeY(); y++)
	{
		for (int x = 0; x < GetSizeX(); x++)
			if (y == (GetSizeY() / 2) && x == (GetSizeX() / 2))
				std::cout << "O";
			else 
				std::cout << cave[y][x];
		std::cout << "\n";
	}
}

void DLA::LifeCycle()
{
	for (int i = 0; i < FileReader::GetInstance().FetchIntData(6); i++) // How many caves shall we generate?
	{
		Init(FileReader::GetInstance().FetchIntData(0),	FileReader::GetInstance().FetchIntData(1));
		/////////////////////////////////////////////
		// Set all locations in the map to walls ////
		// This is just to remove junk-values.
		EmptyCave();
		SpawnBuilder();
		
		/////////////////////////////////////////////
		// Generate the cave(s) /////////////////////
		GenerateCave();
		//PrintCave();
		/////////////////////////////////////////////
		// Save the cave(s) in seperate files ///////
		SaveCave();
		//
		//std::cin.get();
		//system("cls");
	}
	//std::cout << GetCavesGenerated() << "/" << GetCavesToGenerate() << " caves generated and saved.\n";
}

void DLA::SaveCave()
{
	FrameCave();
	SetCavesGenerated(GetCavesGenerated() + 1);
	FileReader::GetInstance().WriteToFile(cave, GetCavesGenerated(), GetSizeY(), GetSizeX(), GetTimeToGenerate());
}