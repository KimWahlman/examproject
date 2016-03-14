#include "DLA.h"

Builder::Builder() 
{
	mStart = new int[2];
	mPos = new int[2];

	mDirection = 0;
	mCorridorLenght = 0;
	mOrthogonallMovementAllowed = false;
}