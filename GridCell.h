#pragma once
#ifndef GridCell_CPP_INCLUDED
#define GridCell_CPP_INCLUDED

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <limits>
#include <random>
#include <utility>
#include "particle.h"

class gridCell
{
public:
	int i, k;
	int cellIdx;
	std::vector<particle> inner;
	std::vector<particle> border;

	bool isBorder(particle); 
	void setgP(int, int);
	void addP(particle);
	void addPIB(particle);
};

#endif

