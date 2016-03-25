#ifndef SFMLSTUFF_H
#define SFMLSTUFF_H

#include <SFML\Graphics.hpp>

class MessyClass
{
	sf::RenderWindow mWindow;
	sf::View mView;
	char** drawFluff;
	sf::RectangleShape mWhite;
	float mCurrX, mCurrY, mCurrZoom;
	int mCaveSizeX, mCaveSizeY;
	bool newSize;

	MessyClass() { }
public:
	~MessyClass() { }
	static MessyClass &GetInstance()
	{
		static MessyClass instance;
		return instance;
	}
	MessyClass(MessyClass const&) = delete;
	void operator=(MessyClass const&) = delete;

	void Init(int sizeX = 1024, int sizeY = 768);
	void DrawWindow();
	void Run();
	void FetchData();
	void DrawMap();
	void Keyboard();
};

#endif
