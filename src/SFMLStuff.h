#ifndef SFMLSTUFF_H
#define SFMLSTUFF_H

#include <SFML\Graphics.hpp>

class MessyClass
{
	char** drawFluff;
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

	void Init();
	void Run();
	void FetchData();
	void SaveImage();
};

#endif
