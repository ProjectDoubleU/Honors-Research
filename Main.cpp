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
#include <fstream>
#include "particle.h"
#include "gridArray.h"
#include "gridCell.h"

//constants 
namespace c {
	double R = 0.01105, L = 0.3023; //size of fluid profile cross section 
	double num = 120.0; //grid divisions of original data 
	double dR = R / num, dZ = L / num;
	double Rdiv = 100.0, Zdiv = 100.0; //grid divisions of 
	double dr = R / Rdiv, dz = L / Zdiv; //gridCell size 
}

int main()
{
	std::ifstream input; 
	std::ofstream file1; 
	std::ofstream file2; 
	std::ofstream file3;
	gridArray ga = gridArray(); //used for brute force and iterative search

	input.open("validation.csv"); 
	ga.initGrid(input); 
	input.close(); 
	std::cout << "Working" << ga.g.size(); 
	file1.open("bruteForceSearch.csv"); 
	file2.open("iterativeSearch.csv"); 

	//outputs file 120x120 with first coordinate in position 0,0 and last in 119, 119
	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			particle o = ga.findClosest(j * c::dR, i * c::dZ); 
			file1 << o.T << ",";
			o = ga.findClosestIterative(j * c::dR, i * c::dZ);
			file2 << o.T << ",";
		}
		file1 << std::endl; 
		file2 << std::endl; 
	}

	file1.close();
	file2.close();

	//ga = gridArray(); 

	/*input.open("validation.csv");
	ga.initGrid(input);
	input.close();

	file3.open("borderSearch.csv"); 


	file3.close(); */
}

//methods for particles 
particle::particle()
{
	r = 0; z = 0; T = 0; S = 0; 
}
void particle::setParticle(double x, double h, double t, double s)
{
	r = x; z = h; T = t; S = s;
}
double particle::calcDist(double rr, double zz)
{
	return sqrt(pow(r - rr, 2) + pow(z - zz, 2)); 
}
int particle::calcGridPos()
{
	int i = r / c::dr, k = z / c::dz; 
	return 100 * i + k; 
}
void particle::print()
{
	std::cout << r << " " << z << " " << T << " " << S << " " << calcGridPos() << std::endl; 
}

//methods for the gridArray("particle space")
void gridArray::initGrid(std::ifstream& in)
{
	std::string x, h, t, s, ur, uz; //input values 
	for (int i = 0; i < 100; i++) //initialize gridCells 
	{
		for (int k = 0; k < 100; k++)
		{
			grid[i * 100 + k].setgP(i, k);
			grid[i * 100 + k].cellIdx = i * 100 + k;
		}
	}

	while (!in.eof()) //read in file and add to gridArray and corresponding cell
	{
		getline(in, x, ',');
		getline(in, h, ',');
		getline(in, t, ',');
		getline(in, s, ',');
		getline(in, ur, ',');
		getline(in, uz);
		particle p;
		p.setParticle(stod(x), stod(h), stod(t), stod(s));
		int pos = p.calcGridPos();
		g.push_back(p); 
		grid[pos].addP(p); 
		if (in.eof()) { break; }
	}
}
void gridArray::findNeighbors(std::vector<gridCell>& arr, gridCell gC) 
{
	for (int r = gC.i - 1; r < gC.i + 2; r++)
	{
		for (int z = gC.k - 1; r < gC.k + 2; z++)
		{
			arr.push_back(grid[r * 100 + z]); 
		}
	}
}
// VVVVV   need to fix  VVVVV
void gridArray::findNeighborsIterative(std::vector<gridCell>& arr, gridCell gC)
{

}
particle gridArray::findClosest(double rr, double zz) 
{
	double distance = 100.00;
	particle closest;
	for (particle o : g)
	{
		if (o.calcDist(rr, zz) < distance)
		{
			distance = o.calcDist(rr, zz);
			closest = o;
		}
	}
	return closest;
}
// VVVVV   need to fix   VVVVV
particle gridArray::findClosestInNeighbors(double rr, double zz)
{
	std::vector<gridCell> neighbors;
	int gC = int(rr / rdiv) * 100 + int(zz / zdiv);
	neighbors.push_back(grid[gC]);
	findNeighbors(neighbors, grid[gC]);

	particle closest = particle(); 
	double distance = 100;
	for (particle p : grid[gC].inner)
	{
		if (distance > p.calcDist(rr, zz))
		{
			distance = p.calcDist(rr, zz);
			closest = p;
		}
	}
	for (gridCell cell : neighbors)
	{
		for (particle u : cell.border)
		{
			if (distance > u.calcDist(rr, zz))
			{
				distance = u.calcDist(rr, zz);
				closest = u;
			}
		}
	}
	neighbors.clear();
	
	return closest;
}
particle gridArray::findClosestIterative(double rr, double zz)
{
	particle closest;
	return closest;
}

//methods for gridCells
void gridCell::setgP(int x, int y)
{
	i = x, k = y; 
}
void gridCell::addP(particle o)
{
	inner.push_back(o); 
}
// VVVVV   need to fix   VVVVV
void gridCell::addPIB(particle o)
{
	
}
// VVVVV   need to fix   VVVVV
bool isBorder(particle o)
{
	return true; 
}