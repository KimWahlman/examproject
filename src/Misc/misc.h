#ifndef MISC_H
#define MISC_H

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

void WriteToFile(char** map, int caveNumber, int y, double time)
{
	std::ofstream file("cave_" + std::to_string(caveNumber) + ".txt");
	if (file.is_open())
	{
		std::cout << "Writing to file...\n";
		file /*<< std::fixed << std::setprecision(25) */<< "Time to generate: " << time << " ms\n";
		for (int i = 0; i < y; i++)
				file << map[i] << "\n";
		file.close();
		std::cout << "All done!\n\n";
		return;
	}
	std::cout << "Couldn't write to file cave_" + std::to_string(caveNumber) + ".txt";
}

#endif