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

	if (position <0 || position > (int)this->getSize()) position=maths::roll.flat(0,this->getSize());

	unsigned byte;
	position % 8>0 ? byte=position/8+1:byte=position/8;

	base2Genome[byte]= base2Genome[byte] ^ maths::roll.bit()<<position;



}

