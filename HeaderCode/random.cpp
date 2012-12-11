/*
 * random.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../Headers/entities.h"
#include "../Headers/random.h"

using namespace maths;


double random::flat(double Min, double Max){
	return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}

int random::flat(int Min, int Max){
	return floor(((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min);
}

unsigned random::bit(){
	return (flat(0,9)%2);
}

double random::gaussian(double sd, double mean) //Based on implementation by Dr Everett Carter @ Taygeta Scientific inc.
{
	double x1,x2, w, z1; //x1 and x2 are the random numbers defined in Boxmuller function

	if (use)
	{
		z1 = storedGaussian;
		use=false;
	}
	else
	{
		do {
			x1 = 2.0 * this->flat(0,1) - 1.0;
			x2 = 2.0 * this->flat(0,1) - 1.0;
			w = x1 * x1 + x2 * x2;
		} while ( w >= 1.0 );

		w = sqrt( (-2.0 * log( w ) ) / w );
		z1 = x1 * w;
		storedGaussian = x2 * w;
	}

	return( mean + z1 * sd ); //To get any mean/sd we scale wrt sd and transform wrt mean (source: http://en.literateprograms.org/Box-Muller_transform_%28C%29)
}

maths::random maths::roll;
