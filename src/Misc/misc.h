#ifndef MISC_H
#define MISC_H

#include <fstream>
#include <istream>
#include <string>
#include <iostream>
#include <iomanip>

// This will be used to decide cave size, birth- and death limits, 
// numbers of generations the sumulation will continue,
// the initial survivial rate and seed.
// Seed = 0 will remove the usage of a seed.

class FileReader
{
	int data[7];			// Will hold information for the system to use.
public:
	FileReader() { }
	~FileReader() { }

	void ReadFromFile(unsigned int numOfLines = 0)
	{
		if (numOfLines == 0)
		{
			std::cout << "Line number must be higher than 0.";
			return;
		}
		std::ifstream file("data.txt");
		if (file.is_open())
		{
			for (int i = 0; i < numOfLines; file >> data[i++]);
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
		std::ofstream file("cave_" + std::to_string(caveNumber) + ".txt");
		if (file.is_open())
		{
			std::cout << "Writing to file...\n";
			file /*<< std::fixed << std::setprecision(25) */ << "Time to generate: " << time << " ms\n";
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					file << map[i][j];
				}
				file << "\n";
			}
			file.close();
			std::cout << "All done!\n\n";
			return;
		}
		std::cout << "Couldn't write to file cave_" + std::to_string(caveNumber) + ".txt";
	}
};
#endif