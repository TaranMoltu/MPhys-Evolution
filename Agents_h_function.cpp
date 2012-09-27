/*
 * Agents_h_function.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Michael Williams
 *	Purpose: Has all functions for Agents.h
 */

#include "Headers/Agents.h"
#include<iostream> //Use to output to console
#include<cstdlib> //Use for random numbers
#include<ctime> //Use to seed pseudorandom numbers

using namespace org; //Use for simplicity: nearly everything in this is in namespace org. This is not bad practice as there is only one namespace in use here


//Start with height functions
gene* height::clone(){
	gene* temp = new height(this->value,this->rate);
	return temp;
}

void height::mutate(){
	double mean = value;
	double sd=rate;
	double x1, x2, w, z1; //x1 and x2 are the random numbers defined in Boxmuller function
	static double z2; //Z2 is the second distributed value
	static int use_last = 0; //The box-muller function generates two values. It is more useful to save this value for the second call
	srand((unsigned)time(0)); //Seeds random numbers based on time of execution;
	if (use_last)		        
	{
		z1 = z2;
		use_last = 0;
	}
	else
	{
		do {
			double RandomNumber = (double(rand()) / double(RAND_MAX)) * (1 - 0) + 0; //Gives a random number between 0 and 1
			x1 = 2.0 * RandomNumber - 1.0;
			RandomNumber = (double(rand()) / double(RAND_MAX)) * (1 - 0) + 0; //Get a new random number between 0 and 1
			x2 = 2.0 * RandomNumber - 1.0; 
			w = x1 * x1 + x2 * x2;
		} while ( w >= 1.0 );
		
		w = sqrt( (-2.0 * log( w ) ) / w );
		z1 = x1 * w;
		z2 = x2 * w;
		use_last = 1;
	}

	value = ( mean + z1 * sd ); //To get any mean/sd we scale wrt sd and transform wrt mean (source: http://en.literateprograms.org/Box-Muller_transform_%28C%29)
}

bool height::selection(){ //NOTE: We need to fix this function
	//taller is better kk.
	if(this->value > 1.5){
		return true;
	}
	else{
		return false;
	}
		}