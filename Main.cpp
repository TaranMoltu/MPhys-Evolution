/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 */

#include "Headers/Agents.h"
#include<iostream> //Use to output to console
#include<cstdlib> //Use for random numbers
#include<ctime> //Use to seed pseudorandom numbers
//Declare constant PI
const double PI = 3.141592;

//Function prototypes
double RandomNumber(double Min, double Max); //Returns a pseudorandom double between Min and Max. Based on http://stackoverflow.com/questions/4310277/producing-random-float-from-negative-to-positive-range


int main(){
	srand((unsigned)time(0)); //Seeds the random number generator based on the time of execution 
	double randomat;
	
	std::cout << "hello world"<<std::endl;
	randomat = RandomNumber(-1*PI, PI);
	std::cout <<randomat<<std::endl;
}

double RandomNumber(double Min, double Max)
{
    return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}
