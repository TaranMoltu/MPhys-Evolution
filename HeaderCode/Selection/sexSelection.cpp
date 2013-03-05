/*
 * sexSelection.cpp
 *
 *  Created on: 7 Feb 2013
 *      Author: joshua
 */

#include "../../Headers/entities.h"

bool org::genome::selection(const org::genome* spouseGenome)const{
	std::vector<gene*>::const_iterator current,begin,end;
	begin = genes.begin();
	end = genes.end();
	unsigned i(0);
	for (current=begin; current<end;++current){//delete all genes
		if(!((*current)->selection(spouseGenome->getGenePointer(i)))) return false;
		i++;
	}
	return true;
}

bool org::height::selection(const org::gene* spouseGene) const{
	double distance(fabs(this->getValue()-spouseGene->getValue()));
	if (distance > (max-min)/2.0) distance =(max-min)-distance;
	//std::cout << distance << " vs " << compatability <<std::endl;
	if (distance<compatability) return true;
	else return false;
}
