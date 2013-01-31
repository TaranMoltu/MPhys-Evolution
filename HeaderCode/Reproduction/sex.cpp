/*
 * sex.cpp
 *
 *  Created on: 30 Jan 2013
 *      Author: joshua
 */

#include "../../Headers/entities.h"

using namespace org;

/*============================================================================
 * Gene Mating
 *========================================================================== */
void height::mate(gene* spouceGene){
	value=(spouceGene->getValue()+this->getValue())/2.0;
}
void genome::mate(genome* spouceGenome){
	std::vector<gene*>::const_iterator current,begin,end;
	begin = genes.begin();
	end = genes.end();
	unsigned i(0);

	for (current=begin; current<end;++current){//mate all genes
		(*current)->mate((*spouceGenome)(i));
		i++;
	}

}


/*============================================================================
 * Sexual reproduction
 *========================================================================== */

entity* entity::sex(entity* spouse){
	//if (!this->selection(spouse)){
	if (false){
		return NULL; //return null pointer if match is not appropriate
	}
	else {
		entity* temp = this->clone();
		temp->mate(spouse);
		temp->mutate();
		return temp;
	}
}
