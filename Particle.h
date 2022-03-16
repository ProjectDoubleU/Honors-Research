#pragma once
#ifndef Particle_CPP_INCLUDED
#define Particle_CPP_INCLUDED

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

class particle {
public:
	double r, z, T, S;
	particle(); 
	void setParticle(double, double, double, double);
	double calcDist(double, double);
	int calcGridPos();
	void print();
};

#endif
