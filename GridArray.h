#pragma once
#ifndef GridArray_CPP_INCLUDED
#define GridArray_CPP_INCLUDED

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
#include "gridCell.h"

class gridArray
{
public:
	double rdiv, zdiv;

	std::vector<particle> g;
	gridCell grid[10000];
	particle findClosest(double, double); //bruteforce
	particle findClosestInNeighbors(double, double); //inner/border regions A
	particle findClosestIterative(double, double); //iterative increase in search range B
	void initGrid(std::ifstream&); 
	void findNeighbors(std::vector<gridCell>& arr, gridCell gC); //helper for A
	void findNeighborsIterative(std::vector<gridCell>& arr, gridCell gC); //helper for B
};

#endif

