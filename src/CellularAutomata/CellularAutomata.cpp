#include "CellularAutomata.h"
#include "../SFMLStuff.h"
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>

#define FLOOR '.'
#define WALL '#'

void CellularAutomata::Init(int sizeX, int sizeY, int birthLimit, int deathLimit, int generations, int changeToStayAlive, int numOfCavesToGenerate, unsigned int seed)
{
	// Do we have a specified seed or will we randomize?
	if (seed != 0)
		std::srand(seed);
	else // Randomize if we don't have a seed
		std::srand((unsigned int)time(NULL));

	// Set values for various things.
	SetSizeX(sizeX);
	SetSizeY(sizeY);
	SetBirthLimit(birthLimit);
	SetDeathLimit(deathLimit);
	SetGenerations(generations);
	SetChanceToStayAlive(changeToStayAlive);
	SetCavesToGenerate(numOfCavesToGenerate);
	SetCavesGenerated(0);

	// Allocate memory for the map. //////////////
	cave = new char*[GetSizeY()];
	cave2 = new char*[GetSizeY()];

	for (int y = 0; y < GetSizeY(); y++) 
	{
		cave[y] = new char[GetSizeX()];
		cave2[y] = new char[GetSizeX()];
	}
	/////////////////////////////////////////////
}

void CellularAutomata::LifeCycle()
{
	FILETIME	prevSysKernel, prevSysUser,
				prevProcKernel, prevProcUser;
	float		usage = 0.0f;
	MessyClass::GetInstance().Init(GetSizeX(), GetSizeY());
	for (int i = 0; i < FileReader::GetInstance().FetchIntData(6); i++) // How many caves shall we generate?
	{
		/////////////////////////////////////////////
		// Set all locations in the map to walls ////
		// This is just to remove junk-values.
		EmptyCave();

		/////////////////////////////////////////////
		// Randomize the initial map ////////////////
		RandomizeCave();

		/////////////////////////////////////////////
		// Generate the cave(s) /////////////////////
		CPUUsage c;
		usage = c.GetCPUUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser, true);
		GenerateCave();
		usage = c.GetCPUUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser);
		FileReader::GetInstance().WriteToFile(std::to_string(GetSizeX()) + "x" + std::to_string(GetSizeY()) + "_CPUUsage.txt", "", usage, 2);
		//PrintCave();
		/////////////////////////////////////////////
		// Save the cave(s) in seperate files ///////
		SaveCave();
		//
		MessyClass::GetInstance().SaveImage(GetCavesGenerated(), GetCave());
	}
	std::cout << "Generation completed!\n\nPress enter to exit program...\n";
}

// Create walls on all edges of the map.
void CellularAutomata::FrameCave()
{
	for (int i = 0; i < GetSizeY(); i++)
	{
		cave[i][0] = cave[i][GetSizeX() - 1] = '#';
		cave2[i][0] = cave2[i][GetSizeX() - 1] = '#';
	}
	for (int i = 0; i < GetSizeX(); i++)
	{
		cave[0][i] = cave[GetSizeY() - 1][i] = '#';
		cave2[0][i] = cave2[GetSizeY() - 1][i] = '#';
	}
}

// Reset the cave to only contain floors.
void CellularAutomata::EmptyCave()
{
	for (int y = 0; y < GetSizeY(); y++)
		for (int x = 0; x < GetSizeX(); x++) 
		{
			cave[y][x] = WALL;
			cave2[y][x] = WALL;
		}
}

// Randomize the initial layout of the cave.
void CellularAutomata::RandomizeCave()
{
	for (int y = 0; y < GetSizeY(); y++)
		for (int x = 0; x < GetSizeX(); x++) {
			if ((std::rand() % 101 < GetChanceToStayAlive())) {
				cave[y][x] = FLOOR; //
			}
		}
		
}

// Debug-function to display the cave.
void CellularAutomata::PrintCave()
{
	for (int y = 0; y < GetSizeY(); y++)
	{
		for (int x = 0; x < GetSizeX(); x++)
			std::cout << cave[y][x];
		std::cout << "\n";
	}
}

// Save the cave in a textfile.
void CellularAutomata::SaveCave()
{
	FrameCave();
	SetCavesGenerated(GetCavesGenerated() + 1);
	Timer t;
	t.StartTimer();
	FileReader::GetInstance().WriteToFile(cave, GetCavesGenerated(), GetSizeY(), GetSizeX(), GetTimeToGenerate());
	t.StopTimer();
}


// How many neighbours is alive around the tile
// The diagram below show why we have -1 and 2
// in the for-loops.
/*
 ___________________________________
|           |           |           |
| (x-1,y-1) | ( x, y-1) | (x+1,y-1) |
|___________|___________|___________|
|           |           |           |
| (x-1, y ) |  (x, y )  | (x+1, y ) |
|___________|___________|___________|
|           |           |           |
| (x-1,y+1) | ( x, y+1) | (x+1,y+1) |
|___________|___________|___________|

*/
int CellularAutomata::CountLivingNeighbours(int x, int y)
{
	int numOfLivingNeighbours = 0;
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			int XNeighbour = x + j;
			int YNeighbour = y + i;

			if (i == 0 && j == 0); // We need to avoid looking on the current tile!
			else if (XNeighbour < 0 || YNeighbour < 0 || XNeighbour >= GetSizeX() || YNeighbour >= GetSizeY())
				numOfLivingNeighbours++;
			else if (cave[YNeighbour][XNeighbour] == FLOOR) //
				numOfLivingNeighbours++;
		}
	return numOfLivingNeighbours;
}

// This will happen in each step of the generation of the cave.
void CellularAutomata::StepInGeneration()
{
	for (int i = 0; i < GetSizeY(); i++)
	{
		for (int j = 0; j < GetSizeX(); j++)
		{
			int livingNeighbours = CountLivingNeighbours(j, i);
			//if (i == 1 && j == 2)
			//	std::cout << livingNeighbours << "\n";
			if (cave[i][j] == FLOOR)
			{
				// If current node is a live but too many neighbours are dead, kill it.
				if (livingNeighbours < GetDeathLimit())
					cave2[i][j] = WALL;
				else
					cave2[i][j] = FLOOR; //
			}
			else// if(cave[i][j] == '#')
			{
				if(livingNeighbours > GetBirthLimit())
					cave2[i][j] = FLOOR; //
				else
					cave2[i][j] = WALL;
			}
		}
	}

	for (int i = 0; i < GetSizeY(); i++)
		for (int j = 0; j < GetSizeX(); j++)
			cave[i][j] = cave2[i][j];
}

// Generate the cave.
// Here we will also time it and calculate the CPU usage.
// TODO(Kim): Calculate CPU usage.
void CellularAutomata::GenerateCave()
{
	Timer t;
	t.StartTimer();
	for (int i = 0; i < GetGenerations(); i++)
		StepInGeneration();
	t.StopTimer();
	SetTimeToGenerate(t.GetDuration());
}