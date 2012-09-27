/*
 * Mutations.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../Headers/entities.h"
#include "../Headers/random.h"

using namespace org;

void height::mutate(){
	double mean = value;
	double sd=rate;
	maths::random rnGenerator;

	value= rnGenerator.gaussian(sd,mean);
}
