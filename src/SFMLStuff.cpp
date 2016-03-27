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
	//drawFluff = new char*[caveX];
	//for (int y = 0; y < caveX; y++)
	//	drawFluff[y] = new char[caveX];

	//for (int y = 0; y < caveX; y++)
	//	for (int x = 0; x < caveX; x++)
	//		drawFluff[y][x] = '#';

	//drawFluff = cave;

 	sf::Uint8* temp;
	temp = new sf::Uint8[caveY * caveX * 4];
	memset(temp, 255, caveY * caveX * 4);

	for (int y = 0; y < caveY; y++) {
		for (int x = 0; x < caveX; x++) {
			if (cave[x][y] == '.') {
				//temp[(y + x * caveY) * 4 + 0] = 255;
				//temp[(y + x * caveY) * 4 + 1] = 255;
				//temp[(y + x * caveY) * 4 + 2] = 255;
				//temp[(y + x * caveY) * 4 + 3] = 255;
			}
			if (cave[x][y] == '#') {
				temp[(y + x * caveY) * 4 + 0] = 0;
				temp[(y + x * caveY) * 4 + 1] = 0;
				temp[(y + x * caveY) * 4 + 2] = 0;
				//temp[(y + x * caveY) * 4 + 3] = 255;
			}
		}
	}

	if (CreateDirectoryA("img", NULL))
	{
		std::cout << "Created \"img\" Directory!\n";
		Sleep(100);
	}

	img.create(caveX, caveY, temp);
	img.saveToFile("img/cave_" + std::to_string(num) + ".png");
	delete[] temp;
	//for (int i = 0; i < caveY; i++)
	//	delete drawFluff[i];
	//delete drawFluff;
}