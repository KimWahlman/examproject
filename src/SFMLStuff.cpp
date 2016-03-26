#include "SFMLStuff.h"
#include "DLA\DLA.h"
#include "CellularAutomata\CellularAutomata.h"

void MessyClass::Init()
{
	drawFluff = new char*[DLA::GetInstance().GetSizeY()];
	for (int y = 0; y < DLA::GetInstance().GetSizeY(); y++)
		drawFluff[y] = new char[DLA::GetInstance().GetSizeX()];

	for (int y = 0; y < DLA::GetInstance().GetSizeY(); y++)
		for (int x = 0; x < DLA::GetInstance().GetSizeX(); x++)
			drawFluff[y][x] = '#';
}

void MessyClass::Run()
{
	FetchData();
	SaveImage();
}

void MessyClass::FetchData()
{
	drawFluff = DLA::GetInstance().GetCave();
}

void MessyClass::SaveImage()
{
	sf::Uint8* temp;
	temp = new sf::Uint8[DLA::GetInstance().GetSizeY() * DLA::GetInstance().GetSizeX() * 4];
	int cx = DLA::GetInstance().GetSizeX(),
		cy = DLA::GetInstance().GetSizeY();

	for (int y = 0; y < cy; y++) {
		for (int x = 0; x < cx; x++) {
			if (drawFluff[x][y] == '.') {
				temp[(y + x * cy) * 4 + 0] = 255;
				temp[(y + x * cy) * 4 + 1] = 255;
				temp[(y + x * cy) * 4 + 2] = 255;
				temp[(y + x * cy) * 4 + 3] = 255;
			}
			if (drawFluff[x][y] == '#') {
				temp[(y + x * cy) * 4 + 0] = 0;
				temp[(y + x * cy) * 4 + 1] = 0;
				temp[(y + x * cy) * 4 + 2] = 0;
				temp[(y + x * cy) * 4 + 3] = 255;
			}
		}
	}

	img.create(DLA::GetInstance().GetSizeX(), DLA::GetInstance().GetSizeY(), temp);
	img.saveToFile("img/cave_" + std::to_string(DLA::GetInstance().GetCavesGenerated()) + ".png");
}