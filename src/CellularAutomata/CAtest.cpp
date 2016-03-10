#include "CAtest.h"
#include "../Misc/misc.h"
#include <random>
#include <ctime>
#include <iostream>

void CATest::Init(int sizeX, int sizeY, int birthLimit, int deathLimit, int generations, int changeToStayAlive, unsigned int seed) {

	// Do we have a specified seed or will we randomize?
	if (seed != 0)
		std::srand(seed);
	else // Randomize if we don't have a seed
		std::srand(time(NULL));

	SetSizeX(sizeX);
	SetSizeY(sizeY);
	SetBirthLimit(birthLimit);
	SetDeathLimit(deathLimit);
	SetGenerations(generations);
	SetChanceToStayAlive(changeToStayAlive);


	// Allocate memory for the map. //////////////
	
	cave = new char*[GetSizeY()];
	cave2 = new char*[GetSizeY()];
	for (int x = 0; x < GetSizeY(); x++) {
		cave[x] = new char[GetSizeY()];
		cave2[x] = new char[GetSizeY()];
	}
	
	/////////////////////////////////////////////

	// Set all locations in the map to walls ////
	// This is just to remove junk-values.
	
	EmptyCave();

	/////////////////////////////////////////////

	// Randomize the initial map ////////////////
	RandomizeCave();

	/////////////////////////////////////////////
}

// Create walls on all edges of the map.
void CATest::FrameCave()
{
	for (int i = 0; i < GetSizeX(); i++)
		cave[i][0] = cave[i][GetSizeX() - 1] = '#';
	for (int i = 0; i < GetSizeY(); i++)
		cave[0][i] = cave[GetSizeY() - 1][i] = '#';
}

// Reset the cave to only contain floors.
void CATest::EmptyCave()
{
	for (int x = 0; x < GetSizeX(); x++)
		for (int y = 0; y < GetSizeY(); y++)
			cave[x][y] = '.';
}

void CATest::RandomizeCave()
{
	for (int x = 0; x < GetSizeX(); x++)
		for (int y = 0; y < GetSizeY(); y++) {
			if (std::rand() % 100 + 1 < GetChanceToStayAlive())
				cave[x][y] = '#';
		}
	cave2 = cave;
	FrameCave();
}

void CATest::PrintCave()
{
	for (int x = 0; x < GetSizeX(); x++)
	{
		for (int y = 0; y < GetSizeY(); y++)
			std::cout << cave2[x][y];
		std::cout << "\n";
	}
	std::cin.get();
}

// How many neighbours is alive around the tile
// A diagram below show why we have -1 and 2
// in the for-loops.
/*

		  x - 1		  x		   x + 1
		______________________________
       |         |          |         |
y - 1  |         |          |         |
       |_________|__________|_________|
	   |         |          |         |
  y    |         |  (x, y)  |         |
	   |_________|__________|_________|
	   |         |          |         |
y + 1  |         |          |         |
	   |_________|__________|_________|


*/
int CATest::CountLivingNeighbours(int x, int y) 
{
	int numOfLivingNeighbours = 0;
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			int XNeighbour = x + i;
			int YNeighbour = y + j;

			if (i == 0 && j == 0); // We need to avoid looking on the current tile!
			else if (XNeighbour < 0 || YNeighbour < 0 || XNeighbour >= GetSizeX() || YNeighbour >= GetSizeY())
				numOfLivingNeighbours++;
			else if (cave[XNeighbour][YNeighbour])
				numOfLivingNeighbours++;
		}
}

// This will happen in each step of the generation of the cave.
void CATest::StepInGeneration()
{
	for (int i = 0; i < GetSizeX(); i++)
	{
		for (int j = 0; j < GetSizeY(); j++)
		{
			int livingNeighbours = CountLivingNeighbours(i, j);
		
		}
	}
}