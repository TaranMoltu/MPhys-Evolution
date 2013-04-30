/*
 * clone.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../../Headers/entities.h"

/*============================================================================
 * Factories
 *========================================================================== */
org::gene* org::height::clone()const{
	gene* temp = new height(this->value,this->standardDeviation,this->rate);
	return temp;
}

org::entity* org::entity::clone()const{
	entity* temp = new entity(this->lifetime,*this);
	return temp;
}

/*============================================================================
 * Asexual reproduction
 *========================================================================== */

org::entity* org::entity::asex(){
	entity* temp = this->clone();
	temp->mutate();
	return temp;
}

