#include "DLA.h"
#include <random>
#include <ctime>
#include <iostream>
#include "../Misc/misc.h"
#include "../SFMLStuff.h"

/// File Structure should be
/// 0. X
/// 1. Y
/// 2. Caves to generate
/// 3. Digsize
/// 4. How much to divide the digsize by
/// 5. How long cooridors can be for a digger
/// 6. Max builder count 
/// 7. Spawn mid or not (1/0).
/// 8. Orthogonal movement ok (1/0).
/// 9. Initial builder count.

#define XYSIZE					FileReader::GetInstance().FetchIntData(0), \
								FileReader::GetInstance().FetchIntData(1)
#define CAVESTOGENERATE			FileReader::GetInstance().FetchIntData(2)
#define DIGSIZE					FileReader::GetInstance().FetchIntData(3)
#define MAKEDIGSIZESMALLER		FileReader::GetInstance().FetchIntData(4)
#define COORIDORLENGHT			FileReader::GetInstance().FetchIntData(5)
#define MAXBUILDERCOUNT			FileReader::GetInstance().FetchIntData(6)
#define SPAWNMID				FileReader::GetInstance().FetchIntData(7)
#define ORTHOGONALOK			FileReader::GetInstance().FetchIntData(8)
#define INITIALBUILDERCOUNT		FileReader::GetInstance().FetchIntData(9)

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
	mOrthogonallMovementAllowed = (ORTHOGONALOK == 1);
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
	 EmptyCave();
	 SetSizeX(sizeX);
	 SetSizeY(sizeY);
	 AllocateMemory();
	 SetAmountOfBuilders(0);
	 SetAllocatedBlocks(0);
	 SetDigSize(DIGSIZE / MAKEDIGSIZESMALLER);
	 SetCavesToGenerate(CAVESTOGENERATE);
	 //	Sleep(3000);
	 
	 mBTemp = 0;
	 mForcedStop = false;
	 mGenerations = 0;
 }

 void DLA::AllocateMemory()
 {
	 cave = new char*[GetSizeY()];
	 for (int y = 0; y < GetSizeY(); y++) 
	 {
		cave[y] = new char[GetSizeX()+1];
		cave[y][GetSizeX()] = '\0';
	 }

	 for (int y = 0; y < GetSizeY(); y++)
		 for (int x = 0; x < GetSizeX(); x++)
			 cave[y][x] = '#';
 }
 
 void DLA::EmptyCave()
 {
	 for (int y = 0; y < GetSizeY(); y++) 
	 {
		 delete[] cave[y];
	 }

	 delete[] cave;

	 mForcedStop = false;
	 SetAllocatedBlocks(0);
	 FlushBuilders();
	 //mBCurr = 0;
	 mBTemp = 0;
 }

 void DLA::CountFloorTiles()
 {
	 mDigged = 0;
	 for (int i = 0; i < GetSizeY() - 1; i++)
		 for (int j = 0; j < GetSizeX() - 1; j++)
			 if (cave[i][j] == '.')
				 mDigged++;
 }

 void DLA::FlushBuilders()
 {
	 int temp = GetAmountOfBuilders();
	 for (int i = 0; i < temp; i++)
		 delete mBuilders[i];	 

	 std::cout << "Flushed " << temp << " builders.\n";
	 mBuilders.clear(); 
	 SetAmountOfBuilders(0);
 } 

void DLA::SpawnBuilder(int amountToSpawn) 
{
	if (mBTemp < MAXBUILDERCOUNT)
	{
		int mx = MAXBUILDERCOUNT;
		if (amountToSpawn > mx) amountToSpawn = MAXBUILDERCOUNT;
		for (int i = 0; i < amountToSpawn; i++)
		{
			if (mBTemp < MAXBUILDERCOUNT)
			{
				mBCurr++;
				mBTemp++;
				mBuilders.push_back(new Builder());
				SetAmountOfBuilders(GetAmountOfBuilders() + 1);
			}
			else
				break;
		}
		for (int i = 0; i < GetAmountOfBuilders(); i++)
		{
			int opt = SPAWNMID;
			int xr = 0, yr = 0;
			if (opt == 0) {
				xr = 1 + std::rand() % (GetSizeX() - 1);
				yr = 1 + std::rand() % (GetSizeY() - 1);
			}
			else if(opt == 1)
			{
				//std::cout << "Spawned in the middle!\n";
				xr = (GetSizeX() - 1) / 2;
				yr = (GetSizeY() - 1) / 2;
			}
			else if (opt == 2)
			{
				if ((std::rand() % 2) == 0) {
					xr = 1 + std::rand() % (GetSizeX() - 1);
					yr = 1 + std::rand() % (GetSizeY() - 1);
					//std::cout << "Spawned here (" << xr << ", " << yr << ")\n";
				}
				else {
					//std::cout << "Spawned in the middle!\n";
					xr = (GetSizeX() - 1) / 2;
					yr = (GetSizeY() - 1) / 2;
				}
			}
			if (xr == 0 || xr == GetSizeX() || yr == 0 || yr == GetSizeY())
			{
				std::cout << "Illegal coordinates, will exit! (" << xr << ", " << yr << ")\n";
				FlushBuilders();
				std::cin.get();
				exit(0);
			}
			mBuilders[i]->SetPosXY(xr, yr);
		}
	}
}

void DLA::StepInGeneration()
{
	if (GetAmountOfBuilders() < 1)
		SpawnBuilder();
	else
	{
		if (GetAmountOfBuilders() == 0) mForcedStop = true;
		while (GetAllocatedBlocks() <= GetDigSize() && !mForcedStop)
		{
			int dir = 0;
			for (int i = 0; i < GetAmountOfBuilders(); i++)
			{
				if (mBuilders[i]->GetOrtogonalMovementAllowed())
					dir = 8;
				else
					dir = 4;

				mBuilders[i]->SetDirection(std::rand() % dir);
				// Norr Y-led
				if (mBuilders[i]->GetDirection() == 0 && mBuilders[i]->GetPosY() > 0)
				{
					mBuilders[i]->SetPosY(mBuilders[i]->GetPosY() - 1);	
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
						if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') {
							mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
							IncrementAllocatedBlocks();
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						}
					}
				}
				// Öst X-led
				else if (mBuilders[i]->GetDirection() == 1 && mBuilders[i]->GetPosX() < GetSizeX())
				{
					mBuilders[i]->SetPosX(mBuilders[i]->GetPosX() + 1);
					
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
						if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') {
							mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
							IncrementAllocatedBlocks();
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						}
					}
				}
				// Syd Y-led
				else if (mBuilders[i]->GetDirection() == 2 && mBuilders[i]->GetPosY() < GetSizeY())
				{
					mBuilders[i]->SetPosY(mBuilders[i]->GetPosY() + 1);
					
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
						if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') {
							mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
							IncrementAllocatedBlocks();
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						}
					}
				}
				// Väst X-led
				else if (mBuilders[i]->GetDirection() == 3 && mBuilders[i]->GetPosX() > 0)
				{
					mBuilders[i]->SetPosX(mBuilders[i]->GetPosX() - 1);
					
					if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) 
					{
						if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') 
						{
							mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
							IncrementAllocatedBlocks();
							cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
						}
					}
				}
				// Nordöst X- och Y-led
				if (mBuilders[i]->GetOrtogonalMovementAllowed()) 
				{
					if (mBuilders[i]->GetDirection() == 4 && mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() > 0)
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() + 1, mBuilders[i]->GetPosY() - 1);
						
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') {
								mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
								IncrementAllocatedBlocks();
								cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							}
						}
					}
					// Sydöst X- och Y-led
					else if (mBuilders[i]->GetDirection() == 5 && mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY())
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() + 1, mBuilders[i]->GetPosY() + 1);
						
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') {
								mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
								IncrementAllocatedBlocks();
								cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							}
						}
					}
					// Sydväst X- och Y-led
					else if (mBuilders[i]->GetDirection() == 6 && mBuilders[i]->GetPosX() > 0 && mBuilders[i]->GetPosY() < GetSizeY())
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() - 1, mBuilders[i]->GetPosY() + 1);
						
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') {
								mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
								IncrementAllocatedBlocks();
								cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							}
						}
					}
					// Nordväst X- och Y-led
					else if (mBuilders[i]->GetDirection() == 7 && mBuilders[i]->GetPosX() > 0 && mBuilders[i]->GetPosY() > 0)
					{
						mBuilders[i]->SetPosXY(mBuilders[i]->GetPosX() - 1, mBuilders[i]->GetPosY() - 1);
						
						if (mBuilders[i]->GetPosX() < GetSizeX() && mBuilders[i]->GetPosY() < GetSizeY()) {
							if (cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] != '.') {
								mBuilders[i]->SetCorridorLenght(mBuilders[i]->GetCorridorLenght() + 1);
								IncrementAllocatedBlocks();
								cave[mBuilders[i]->GetPosY()][mBuilders[i]->GetPosX()] = '.';
							}
						}
					}
				}

				if (mBuilders[i]->GetCorridorLenght() >= (COORIDORLENGHT))
				{
					delete mBuilders[i];
					mBuilders.erase(mBuilders.begin() + i);
					SetAmountOfBuilders(GetAmountOfBuilders() - 1);
					SpawnBuilder(1);
				}

				// Ensure that builder is touching an existing spot
				if ((mBuilders[i]->GetPosX() < (GetSizeX() - 1) && mBuilders[i]->GetPosY() < (GetSizeY() - 1) &&
					mBuilders[i]->GetPosX() > 1 && mBuilders[i]->GetPosY() > 1));
				else
				{
					int xr = 1 + std::rand() % (GetSizeX() - 1);
					int yr = 1 + std::rand() % (GetSizeY() - 1);
					mBuilders[i]->SetPosXY(xr, yr);
				}
				if (GetAmountOfBuilders() == 0) mForcedStop = true;
			}
		}
		FlushBuilders();
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

	FILETIME	prevSysKernel, prevSysUser,
				prevProcKernel, prevProcUser;
	double		usage = 0.0;

	Init(XYSIZE);
	MessyClass::GetInstance().Init(GetSizeX(), GetSizeY());
	
	for (int i = 0; i < CAVESTOGENERATE; i++) // How many caves shall we generate?
	{
		
		/////////////////////////////////////////////
		// Set all locations in the map to walls ////
		// This is just to remove junk-values.
		EmptyCave();
		AllocateMemory();
		SpawnBuilder(INITIALBUILDERCOUNT);
		/////////////////////////////////////////////
		// Generate the cave(s) /////////////////////
		CPUUsage c;
		usage = c.GetCPUUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser, true);
		Timer t;
		t.StartTimer();
		GenerateCave();
		t.StopTimer();
		usage = c.GetCPUUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser);
		std::cout << "Usage = " << usage << "\n";
		SetTimeToGenerate(t.GetDuration());
		FileReader::GetInstance().WriteToFile(std::to_string(GetSizeX()) + "x" + std::to_string(GetSizeY()) + "_CPUUsage.txt", "", usage, 8);
		/////////////////////////////////////////////
		// Save the cave(s) in seperate files ///////
		SaveCave();
		MessyClass::GetInstance().SaveImage(GetCavesGenerated(), GetCave());
		//std::cout << "GetCavesToGenerate() = " << GetCavesToGenerate() << "\n";
		system("CLS");
		CountFloorTiles();
		std::cout << "[ CAVE " << GetCavesGenerated() << " / " << GetCavesToGenerate() << " COMPLETED ]\n";// Final builder count \t = " << mBTemp << "\nDigged blocks \t\t = " << GetDigged() << " / " << GetDigSize() << "\n\n";
		std::cout << "Excavated Blocks  = " << GetDigged() << " / " << GetDigSize() << "\n";
		std::cout << "Total amount of builders spawned in current cave = " << mBTemp << "\n";
	}
	//std::cout << "GetCavesToGenerate() = " << GetCavesToGenerate() << "\n";
	CPUUsage c;
	c.FindUsage("Data/" +std::to_string(DLA::GetInstance().GetSizeX()) + "x" + std::to_string(DLA::GetInstance().GetSizeY()) + "_CPUUSAGE.txt", DLA::GetInstance().GetSizeX(), DLA::GetInstance().GetSizeY(), FileReader::GetInstance().FetchIntData(2));
	std::cout << "Total amount of builders spawned in all caves = " << mBCurr << "\n\n"; "Generation completed!\nPress enter to exit program...\n";
}

void DLA::SaveCave()
{
	FrameCave();
	SetCavesGenerated(GetCavesGenerated() + 1);
	FileReader::GetInstance().WriteToFile(cave, GetCavesGenerated(), GetSizeY(), GetSizeX(), GetTimeToGenerate());
}