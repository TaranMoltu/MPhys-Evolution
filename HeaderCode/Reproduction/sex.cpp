/*
 * sex.cpp
 *
 *  Created on: 30 Jan 2013
 *      Author: joshua
 */

#include "../../Headers/entities.h"
#include "../../Headers/random.h"

using namespace org;

/*============================================================================
 * Gene Mating
 *========================================================================== */
void height::mate(gene* spouceGene){
	if(fabs(spouceGene->getValue()-this->getValue())<maths::pi){
		value=(spouceGene->getValue()+this->getValue())/2.0;
	}else{
		if (spouceGene->getValue() > this->getValue()){
			value=(spouceGene->getValue()+this->getValue()+2*maths::pi)/2.0;
		}else{
			value=(spouceGene->getValue()+this->getValue()-2*maths::pi)/2.0;
		}
	}


	while(value  > max){
			value = value -(max-min);
		}

	while(value  < min){
		value = value +(max-min);
	}
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
	if (!this->selection(spouse)){
	//if (false){
		return NULL; //return null pointer if match is not appropriate
	}
	else {
		entity* temp = this->clone();
		temp->mate(spouse);
		temp->mutate();
		return temp;
	}
}
