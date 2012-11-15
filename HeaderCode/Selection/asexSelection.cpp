/*
 * asexSelection.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../../Headers/entities.h"

using namespace org;

unsigned genome::distance(genome &compare) const{
	unsigned distance(fabs(this->getSize()-compare.getSize())), size;
	this->getSize() > compare.getSize() ? size = compare.getSize(): size = this->getSize();

	for (unsigned i(0); i < size; i++) if(((*this)(i)) != compare(i)) distance++;

	return distance;

}
unsigned entity::distance(entity &compare) const{
	unsigned distance(fabs(this->getSize()-compare.getSize())), size;
	this->getSize() > compare.getSize() ? size = compare.getSize(): size = this->getSize();

	for (unsigned i(0); i < size; i++) if(((*this)(i)) != compare(i)) distance++;

	return distance;
}
