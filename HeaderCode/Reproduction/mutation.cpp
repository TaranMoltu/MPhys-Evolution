/*
 * Mutations.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../../Headers/entities.h"
#include "../../Headers/random.h"

using namespace org;

void genome::mutatePoint(int position){
	std::vector<int>::iterator begin;
	begin = base2Genome.begin();


	if (position <0 || position > (int)this->getSize()) position=maths::roll.flat(0,this->getSize());

	*(begin+position)=maths::roll.bit();

	//for (current=begin; current<end;++current){//mutate all genes
	//	(*current)->mutate();
	//}
}

