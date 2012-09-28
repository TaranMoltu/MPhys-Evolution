/*
 * clone.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../../Headers/entities.h"

using namespace org;

/*============================================================================
 * Factories
 *========================================================================== */
gene* height::clone()const{
	gene* temp = new height(this->value,this->standardDeviation,this->rate);
	return temp;
}

entity* entity::clone()const{
	entity* temp = new entity(this->lifetime,*this);
	return temp;
}

/*============================================================================
 * Asexual reproduction
 *========================================================================== */

entity* entity::asex(){
	entity* temp = this->clone();
	temp->mutate();
	return temp;
}

