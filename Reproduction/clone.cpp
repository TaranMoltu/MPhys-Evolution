/*
 * clone.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../Headers/entities.h"

using namespace org;

/*============================================================================
 * Factories
 *========================================================================== */


entity* entity::clone(){
			entity* temp = new entity(this->lifetime, this->props);
			return temp;
		}

/*============================================================================
 * Asexual reproduction
 *========================================================================== */

entity* entity::asex(){
	entity* temp = this->clone();
	temp->props.mutate();
	return temp;
}
