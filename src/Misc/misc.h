#ifndef MISC_H
#define MISC_H

#include <random>
#include <ctime>
#include <iostream>

double dRand(double min, double max)
{
	double f = min + ((double)rand() / RAND_MAX) * (max - min);
	std::cout << f;
	return f;
}

#endif
