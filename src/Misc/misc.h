#ifndef MISC_H
#define MISC_H

#include <fstream>
#include <string>
#include <iostream>

void WriteToFile(char** map, int caveNumber, int y)
{
	std::ofstream file("cave_" + std::to_string(caveNumber) + ".txt");
	if (file.is_open())
	{
		std::cout << "Writing to file...\n";
		for (int i = 0; i < y; i++)
				file << map[i] << "\n";
		file.close();
		std::cout << "All done!\n\n";
		return;
	}
	std::cout << "Couldn't write to file cave_" + std::to_string(caveNumber) + ".txt";
}

#endif