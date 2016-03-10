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
	for (int x = 0; x < GetSizeY(); x++) {
		cave[x] = new char[GetSizeY()];
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
	FrameCave();
}

void CATest::PrintCave()
{
	for (int x = 0; x < GetSizeX(); x++)
	{
		for (int y = 0; y < GetSizeY(); y++)
			std::cout << cave[x][y];
		std::cout << "\n";
	}
	std::cin.get();
}