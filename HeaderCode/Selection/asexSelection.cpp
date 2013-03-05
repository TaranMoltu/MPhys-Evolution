/*
 * asexSelection.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#include "../../Headers/entities.h"

bool org::height::selection()const{ //NOTE: We need to fix this function
	//taller is better kk.
	if(this->value > 1.5){
		return true;
	}
	else{
		return false;
	}
}

