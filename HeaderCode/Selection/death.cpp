#include "../../Headers/random.h"
#include "../../Headers/entities.h"

using namespace org;

bool entity::death(double evFactor){

	if (maths::roll.flat(0,1)>evFactor+0.5) return false;

	else{

	delete this;
	return true;
	}

}
