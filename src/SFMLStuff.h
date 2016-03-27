#ifndef SFMLSTUFF_H
#define SFMLSTUFF_H

#include <SFML\Graphics.hpp>

class MessyClass
{
	char** drawFluff;
	int caveX, caveY;
	sf::Image img;
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

	void Init(int cx, int cy);
	void Run(char** cave, int num);
	void FetchData(char** cave);
	void SaveImage(int num, char** cave);
};

#endif
