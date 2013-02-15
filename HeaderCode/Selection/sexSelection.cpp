/*
 * sexSelection.cpp
 *
 *  Created on: 7 Feb 2013
 *      Author: joshua
 */




#include "../../Headers/entities.h"

using namespace org;


bool genome::selection(const genome* spouseGenome)const{
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

bool height::selection(const org::gene* spouseGene) const{
	if (fabs(this->getValue()-spouseGene->getValue())<compatability) return true;
	else return false;
}
