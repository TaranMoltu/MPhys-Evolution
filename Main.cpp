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
#include<vector> //Use for debugging
#include<fstream> //Use for debugging

//Declare constant PI
const double PI = 3.141592;

//Function prototypes
double RandomNumber(double Min, double Max); //Returns a pseudorandom double between Min and Max. Based on http://stackoverflow.com/questions/4310277/producing-random-float-from-negative-to-positive-range
double BoxMullerTransform(double sd, double mean); //Returns a value from a normal distribution based on Box-Muller Transform

int main(){
	srand((unsigned)time(0)); //Seeds the random number generator based on the time of execution 
	double randomat;
	std::ofstream output("output.txt");
	std::vector<double> bmt_values;

	std::cout << "hello world"<<std::endl;
	randomat = RandomNumber(-1*PI, PI);
	std::cout <<randomat<<std::endl;

	std::cout<< "Test of Box-Muller function"<<std::endl;

	std::cout<<"Mean = 5, standard deviation = 2"<<std::endl;

	for (int i=0; i<1000; i++)
	{
		bmt_values.push_back(BoxMullerTransform(2,5));
		output << bmt_values.back()<<std::endl;
	}
}

double RandomNumber(double Min, double Max)
{
    return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}

double BoxMullerTransform(double sd, double mean) //Based on implementation by Dr Everett Carter @ Taygeta Scientific inc.
{
	double x1, x2, w, z1; //x1 and x2 are the random numbers defined in Boxmuller function
	static double z2; //Z2 is the second distributed value
	static int use_last = 0; //The box-muller function generates two values. It is more useful to save this value for the second call

	if (use_last)		        
	{
		z1 = z2;
		use_last = 0;
	}
	else
	{
		do {
			x1 = 2.0 * RandomNumber(0,1) - 1.0;
			x2 = 2.0 * RandomNumber(0,1) - 1.0;
			w = x1 * x1 + x2 * x2;
		} while ( w >= 1.0 );

		w = sqrt( (-2.0 * log( w ) ) / w );
		z1 = x1 * w;
		z2 = x2 * w;
		use_last = 1;
	}

	return( mean + z1 * sd ); //To get any mean/sd we scale wrt sd and transform wrt mean (source: http://en.literateprograms.org/Box-Muller_transform_%28C%29)
}