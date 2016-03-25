#include "SFMLStuff.h"
#include "DLA\DLA.h"
#include "CellularAutomata\CellularAutomata.h"
#include "Misc\misc.h"
#include <iostream>

#define SIZEX 10.0f
#define SIZEY 10.0f

void MessyClass::Init(int sizeX, int sizeY)
{
	mWindow.create(sf::VideoMode(sizeX, sizeY), "test");
	mWindow.setTitle("Exjobb - DLA");
	mView.setSize((float)sizeX, float(sizeY));
	mView.zoom(20.0f);
	mView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	//mView.setCenter(DLA::GetInstance().GetSizeX(), DLA::GetInstance().GetSizeY());
	mView.setCenter(sizeX / 2, sizeY / 2);
	drawFluff = new char*[DLA::GetInstance().GetSizeY()];
	for (int y = 0; y < DLA::GetInstance().GetSizeY(); y++)
		drawFluff[y] = new char[DLA::GetInstance().GetSizeX()];

	for (int y = 0; y < DLA::GetInstance().GetSizeY(); y++)
		for (int x = 0; x < DLA::GetInstance().GetSizeX(); x++)
			drawFluff[y][x] = '#';

	mWhite.setSize(sf::Vector2f(SIZEX, SIZEY));
	mWhite.setFillColor(sf::Color::White);
	mCurrX = 0.0f;
	mCurrY = 0.0f;
	mCaveSizeX = DLA::GetInstance().GetSizeX();
	mCaveSizeY = DLA::GetInstance().GetSizeX();
	mCurrZoom = 1.0f;
}

void MessyClass::DrawWindow()
{
	mWindow.clear();
	mWindow.setView(mView);
	DrawMap();
	mWindow.display();
}

void MessyClass::Run()
{
	FetchData();
	while (mWindow.isOpen())
	{
		sf::Event _event;
		while (mWindow.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				mWindow.close();
				exit(0);
			}
		}
		Keyboard();
		DrawWindow();
	}
}

void MessyClass::Keyboard()
{
	float tempX = (mCaveSizeX / 2);
	float tempY = (mCaveSizeX / 2);//(mCaveSizeY / (mCaveSizeY / 2));
	if (tempX < 1.0f) tempX = 10.0f;
	if (tempY < 1.0f) tempX = 10.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mView.move(tempX, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mView.move(-tempX, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mView.move(0, tempY);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mView.move(0, -tempY);
	}
	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	//	std::cout << mCurrZoom << "\n";
	//	mWindow.setKeyRepeatEnabled(false);
	//	mCurrZoom += 1.0f;
	//	mView.zoom(mCurrZoom);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
	//	std::cout << mCurrZoom << "\n";
	//	mWindow.setKeyRepeatEnabled(false);
	//	mCurrZoom -= 1.0f;
	//	mView.zoom(mCurrZoom);
	//}
}

void MessyClass::FetchData()
{
	drawFluff = DLA::GetInstance().GetCave();
	mCaveSizeX = DLA::GetInstance().GetSizeX();
	mCaveSizeY = DLA::GetInstance().GetSizeY();
	//mWindow.setSize(sf::Vector2u(mCaveSizeX, mCaveSizeY));
	//for (int y = 0; y < DLA::GetInstance().GetSizeY(); y++) {
	//	for (int x = 0; x < DLA::GetInstance().GetSizeX(); x++)
	//		std::cout << drawFluff[y][x];
	//	std::cout << "\n";
	//}
}

void MessyClass::DrawMap()
{
	for (int y = 0; y < DLA::GetInstance().GetSizeY(); y++)
	{
		for (int x = 0; x < DLA::GetInstance().GetSizeX(); x++)
		{
			
			if (drawFluff[y][x] == '.') 
			{
				mWhite.setPosition(mCurrX, mCurrY);
				mWindow.draw(mWhite);
			}
			mCurrX += SIZEX;
		}
		mCurrX = 0.0f;
		mCurrY += SIZEY;
	}
	mCurrX = 0.0f;
	mCurrY = 0.0f;
}