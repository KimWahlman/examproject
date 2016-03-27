#include "DLA.h"
#include <random>
#include <ctime>
#include <iostream>
#include "../Misc/misc.h"
#include "../SFMLStuff.h"

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
	mOrthogonallMovementAllowed = true;
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

 void DLA::Init(int sizeX, int sizeY)
 {
	 // Do we have a specified seed or will we randomize?
	 // Randomize
	 SetSizeX(sizeX);
	 SetSizeY(sizeY);
	 SetAmountOfBuilders(0);
	 SetAllocatedBlocks(0);
	 SetDigSize((GetSizeY() * GetSizeX()) / 2);
	 //	Sleep(3000);
	 EmptyCave();
 }

 void DLA::AllocateMemory()
 {
	 cave = new char*[GetSizeY()];
	 for (int y = 0; y < GetSizeY(); y++) {
		cave[y] = new char[GetSizeX()+1];
		cave[y][GetSizeX()] = '\0';
	 }
 }

 void DLA::EmptyCave()
 {
	 delete[] cave;
	 AllocateMemory();
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
	 }
	 mBuilders.clear();
	 //mBuilders.pop_back();
	 SetAmountOfBuilders(0);
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
		bool opt = true;
		int xr = 0, yr = 0;
		if (opt) {
			//std::cout << "Spawned here (";
			xr = 1 + std::rand() % (GetSizeX() - 1);
			yr = 1 + std::rand() % (GetSizeY() - 1);
			//std::cout << xr << ", " << yr << ")\n";
		}
		else
		{
			xr = (GetSizeX() - 1) / 2;
			yr = (GetSizeY() - 1) / 2;
		}
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
		// DEBUG TEXT -v
		//std::cout << "GENERATION!\n"
		//	<< "AllocatedBlocks() = " << GetAllocatedBlocks() << "\n"
		//	<< "GetDigSize() = " << GetDigSize() << "\n";
		// DEBUG TEXT -^
		//mBuilders[0]->SetPosXY(GetSizeX(), GetSizeY());
		while (GetAllocatedBlocks() <= GetDigSize())
		{
			//
			// DEBUG TEXT -v
			//system("cls");
			//PrintCave();
			//std::cout << "Stepping...\n";
			//std::cout << "GetAllocatedBlocks() = " << GetAllocatedBlocks() << ", mDigSize = " << (mDigSize) << "\n";
			//std::cout << "Builders = " << GetAmountOfBuilders() << "\n";
			// DEBUG TEXT -^
			for (int i = 0; i < GetAmountOfBuilders(); i++)
			{
				//std::srand((unsigned int)time(0));
				// (double)rand() / ((double)RAND_MAX + 1.0)) * (max - min + 1) + min
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
					mBuilders[i]->GetPosX() > 1 && mBuilders[i]->GetPosY() > 1) && mBuilders[i]->GetCorridorLenght() <= (GetDigSize() / 50000));
				else 
				{ 
					FlushBuilders();
					SpawnBuilder();	
				}
			}
		}
		SetAllocatedBlocks(0);
	}
}

void DLA::GenerateCave() 
{
	Timer t;
	t.StartTimer();
	DLA::GetInstance().StepInGeneration();
	t.StopTimer();
	SetTimeToGenerate(t.GetDuration());
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
	std::srand((unsigned int)time(NULL));
	Init(FileReader::GetInstance().FetchIntData(0), FileReader::GetInstance().FetchIntData(1));
	MessyClass::GetInstance().Init(GetSizeX(), GetSizeY());
	for (int i = 0; i < FileReader::GetInstance().FetchIntData(6); i++) // How many caves shall we generate?
	{
		
		/////////////////////////////////////////////
		// Set all locations in the map to walls ////
		// This is just to remove junk-values.
		EmptyCave();
		SpawnBuilder();
		/////////////////////////////////////////////
		// Generate the cave(s) /////////////////////
		GenerateCave();

		//PrintCave();
		//std::cin.get();

		/////////////////////////////////////////////
		// Save the cave(s) in seperate files ///////
		Timer t;
		t.StartTimer();
		SaveCave();
		t.StopTimer();
		std::cout << t.GetDuration() << "ms\n";
		MessyClass::GetInstance().SaveImage(GetCavesGenerated(), GetCave());
		//std::cin.get();
		//system("cls");
	}
	std::cout << "Generation completed!\n\nPress enter to exit program...\n";
}

void DLA::SaveCave()
{
	FrameCave();
	SetCavesGenerated(GetCavesGenerated() + 1);
	FileReader::GetInstance().WriteToFile(cave, GetCavesGenerated(), GetSizeY(), GetSizeX(), GetTimeToGenerate());
}