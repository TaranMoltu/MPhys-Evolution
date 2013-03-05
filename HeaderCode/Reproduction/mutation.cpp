/*
 * Mutations.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../../Headers/entities.h"
#include "../../Headers/random.h"

void org::genome::mutate(){
	std::vector<org::gene*>::const_iterator current,begin,end;
	begin = genes.begin();
	end = genes.end();

	for (current=begin; current<end;++current){//mutate all genes
		(*current)->mutate();
	}
}

void org::height::mutate(){
	double mean = value;
	double sd= standardDeviation;

	value=maths::roll.gaussian(sd,mean);
	while(value  > max){
		value = value -(max-min);
	}

	while(value  < min){
		value = value +(max-min);
	}
}
