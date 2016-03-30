#include "SFMLStuff.h"
#include "DLA\DLA.h"
#include "CellularAutomata\CellularAutomata.h"

void MessyClass::Init(int cx, int cy)
{
	caveX = cx;
	caveY = cy;
}

void MessyClass::Run(char** cave, int num)
{
	//drawFluff = cave;
	//FetchData(cave);
	//SaveImage(num);
}

void MessyClass::FetchData(char** cave)
{
	drawFluff = cave;
}

void MessyClass::SaveImage(int num, char** cave)
{
 	sf::Uint8* temp;
	temp = new sf::Uint8[caveY * caveX * 4];
	memset(temp, 255, caveY * caveX * 4);

	for (int y = 0; y < caveY; y++) {
		for (int x = 0; x < caveX; x++) {
			if (cave[y][x] == '#') {
				temp[(x + y * caveX) * 4 + 0] = 0;
				temp[(x + y * caveX) * 4 + 1] = 0;
				temp[(x + y * caveX) * 4 + 2] = 0;
			}

			// Set center tile to red
			if (y == (caveY / 2) && x == (caveX / 2))
			{
				temp[(x + y * caveX) * 4 + 0] = 255;
				temp[(x + y * caveX) * 4 + 1] = 0;
				temp[(x + y * caveX) * 4 + 2] = 0;
			}
		}
	}

	if (CreateDirectoryA("img", NULL))
	{
		std::cout << "Created \"img\" Directory!\n";
		Sleep(100);
	}

	img.create(caveX, caveY, temp);
	img.saveToFile("img/" + std::to_string(caveX) + "x" + std::to_string(caveY) + "_cave_" + std::to_string(num) + ".png");
	delete[] temp;
}