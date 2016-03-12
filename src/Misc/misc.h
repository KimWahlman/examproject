#ifndef MISC_H
#define MISC_H

#include <fstream>
#include <istream>
#include <string>
#include <iostream>
#include <iomanip>
#include <Windows.h>
// This will be used to decide cave size, birth- and death limits, 
// numbers of generations the sumulation will continue,
// the initial survivial rate and seed.
// Seed = 0 will remove the usage of a seed.

class FileReader
{
	int data[8];			// Will hold information for the system to use.
	FileReader() { }
public:

	static FileReader &GetInstance()
	{
		static FileReader instance;
		return instance;
	}

	FileReader(FileReader const&) = delete;
	void operator=(FileReader const&) = delete;

	~FileReader() { }

	void ReadFromFile(unsigned int numOfLines = 0)
	{
		if (CreateDirectoryA("Caves", NULL)) 
		{
			std::cout << "Created Directory!";
			Sleep(100);
		}

		if (numOfLines == 0)
		{
			std::cout << "Line number must be higher than 0.";
			return;
		}

		std::ifstream file("data.txt");
		if (file.is_open())
		{
			for (unsigned int i = 0; i < numOfLines; file >> data[i++]);
			file.close();
		}
		else
		{
			std::cout << "Couldn't read file!\n";
			std::cin.get();
			exit(0);
		}
	}

	int FetchData(int i) const
	{
		return data[i];
	}

	void WriteToFile(char** map, int caveNumber, int y, int x, double time)
	{
		std::ofstream file("caves/cave_" + std::to_string(caveNumber) + ".txt");
		if (file.is_open())
		{
			file << "Time to generate: " << time << " ms\n";
			for (int i = 0; i < y; i++)
			{
				for (int j = 0; j < x; j++)
				{
					file << map[i][j];
				}
				file << "\n";
			}
			file.close();
			return;
		}
		std::cout << "Couldn't write to file cave_" + std::to_string(caveNumber) + ".txt";
	}
};
#endif