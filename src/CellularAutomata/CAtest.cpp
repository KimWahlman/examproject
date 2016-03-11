#include "CAtest.h"
#include "../Misc/misc.h"
#include <random>
#include <ctime>
#include <iostream>
#include <Windows.h>
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

	for (int y = 0; y < GetSizeY(); y++) {
		cave[y] = new char[GetSizeX()];
		cave2[y] = new char[GetSizeX()];
	}

	/////////////////////////////////////////////

	// Set all locations in the map to walls ////
	// This is just to remove junk-values.

	EmptyCave();

	/////////////////////////////////////////////

	// Randomize the initial map ////////////////
	RandomizeCave();
	PrintCave();
	/////////////////////////////////////////////
}

// Create walls on all edges of the map.
void CATest::FrameCave()
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
void CATest::EmptyCave()
{
	for (int y = 0; y < GetSizeY(); y++)
		for (int x = 0; x < GetSizeX(); x++) 
		{
			cave[y][x] = '.';
			cave2[y][x] = '.';
		}
}

void CATest::RandomizeCave()
{
	for (int y = 0; y < GetSizeY(); y++)
		for (int x = 0; x < GetSizeX(); x++)
			if (std::rand() % 100 + 1 < GetChanceToStayAlive())
				cave[y][x] = '#';
	//cave2 = cave;
	//FrameCave();
}

void CATest::PrintCave()
{
	FrameCave();
	for (int y = 0; y < GetSizeY(); y++)
	{
		for (int x = 0; x < GetSizeX(); x++)
			std::cout << cave[y][x];
		std::cout << "\n";
	}

	//for (int y = 0; y < GetSizeY(); y++)
	//{
	//	for (int x = 0; x < GetSizeX(); x++)
	//		std::cout << cave2[y][x];
	//	std::cout << "\n";
	//}


	Sleep(1000);
	//system("cls");
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
int CATest::CountLivingNeighbours(int x, int y)
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
			else if (cave[YNeighbour][XNeighbour] == '#')
				numOfLivingNeighbours++;
		}
	return numOfLivingNeighbours;
}

// This will happen in each step of the generation of the cave.
void CATest::StepInGeneration()
{
	//char** temp = new char*[GetSizeY()];
	//for (int y = 0; y < GetSizeY(); y++)
	//	temp[y] = new char[GetSizeX()];

	//for (int i = 0; i < GetSizeY(); i++)
	//	*(temp)[i] = *(cave[i]);

	for (int i = 0; i < GetSizeY(); i++)
	{
		for (int j = 0; j < GetSizeX(); j++)
		{
		//	PrintCave();
			int livingNeighbours = CountLivingNeighbours(j, i);
			if (i == 1 && j == 2)
				std::cout << livingNeighbours << "\n";
			if (cave[i][j] == '#') 
			{
				// If current node is a live but too many neighbours are dead, kill it.
				if (livingNeighbours < GetDeathLimit())
					cave2[i][j] = '.';
				else
					cave2[i][j] = '#';
			}
			else// if(cave[i][j] == '#')
			{
				if(livingNeighbours > GetBirthLimit())
					cave2[i][j] = '#';
				else
					cave2[i][j] = '.';
			}
			//std::cout << "living neighbours around ( " << i << ", " << j << " ) = " << livingNeighbours << "\n";
		}
	}

	//for (int y = 0; y < GetSizeY(); y++)
	//{
	//	for (int x = 0; x < GetSizeX(); x++)
	//		std::cout << cave[y][x];
	//	std::cout << "\n";
	//}

	for (int i = 0; i < GetSizeY(); i++)
		for (int j = 0; j < GetSizeX(); j++)
			cave[i][j] = cave2[i][j];

	//for (int y = 0; y < GetSizeY(); y++)
	//{
	//	for (int x = 0; x < GetSizeX(); x++)
	//		std::cout << cave2[y][x];
	//	std::cout << "\n";
	//}

	//std::cout << "--------------------------------------------\n";

	//for (int i = 0; i < GetSizeY(); i++)
	//	*(cave2[i]) = *(temp[i]);
	//return cave2;
}

void CATest::GenerateCave()
{
	for (int i = 0; i <= GetGenerations(); i++) {
		StepInGeneration();
		PrintCave();
		std::cin.get();
	}
}