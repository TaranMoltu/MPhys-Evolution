/*
 * asexSelection.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../../Headers/entities.h"

using namespace org;

unsigned genome::distance(genome &compare) const{
	unsigned dist = 0,val,bytes;
		size % 8>0 ? bytes=size/8+1:bytes=size/8;
		for(unsigned i(0);i<bytes;++i){
			val = (unsigned)(base2Genome[i] ^ compare.getGenomeByte(i));
			while(val){
				++dist;
				val &= val - 1;
			}
		}

	return dist;
}

unsigned entity::distance(entity &compare) const{
	unsigned dist = 0,val,bytes;
	size % 8>0 ? bytes=size/8+1:bytes=size/8;
	for(unsigned i(0);i<bytes;++i){
		val = (unsigned)(base2Genome[i] ^ compare.getGenomeByte(i));
		while(val){
			++dist;
			val &= val - 1;
		}
	}

	return dist;
}

bool org::height::selection()const{


return true;
}

double org::entity::competition(entity& comp, double& reach)const{
	double difference(distance(comp));

	return exp(-1.0*pow(difference,2.0)/(2.0*pow(reach,2.0)));
}

