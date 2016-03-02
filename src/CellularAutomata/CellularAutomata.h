#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#define FLOOR 0;
#define WALL  1;

typedef struct 
{
	// TODO: Fixa b�ttre dokumentation
	int WallNeighbours1,	// Hur m�nga grannar �r v�ggar?
		WallNeighbours2;

	int RepeatSimXTurns;	// How many generations will we generated?
} GenerationParameters;

class CellularAutomata
{
	double	FillProbability;
	int		SizeX, SizeY;
public:
};

#endif
