/*
 * sex.cpp
 *
 *  Created on: 30 Jan 2013
 *      Author: joshua
 */

#include "../../Headers/entities.h"

/*============================================================================
 * Gene Mating
 *========================================================================== */
void org::height::mate(gene* spouseGene){
	double parentValue=this->getValue();
	if(fabs(spouseGene->getValue()-parentValue)<(max-min)/2.0){
		value=(spouseGene->getValue()+parentValue)/2.0;
	}else{
		value=(max-min)/2.0-fabs(spouseGene->getValue()-parentValue)/2.0;
		spouseGene->getValue() > parentValue ? value+=spouseGene->getValue() :value+=parentValue;
	}

	while(value  > max){
			value = value -(max-min);
		}

	while(value  < min){
		value = value +(max-min);
	}
	//std::cout << "mating " <<spouseGene->getValue() << " and " << parentValue << "to get " << value <<std::endl;
}
void org::genome::mate(genome* spouceGenome){
	std::vector<org::gene*>::const_iterator current,begin,end;
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

org::entity* org::entity::sex(entity* spouse){
	if(this == spouse){
		return NULL;//don't breed with self
	}
	else if (!this->selection(spouse)){
		return NULL; //return null pointer if match is not appropriate
	}
	else {
		org::entity* temp = this->clone();
		temp->mate(spouse);
		temp->mutate();
		return temp;
	}
}
