/*
 * death.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua Warburton
 *  Purpose: decides whether an organism dies or lives - please don't
 *  tell the university ethics committee that we are doing this by a
 *  dice roll. They probably wouldn't be impressed.
 */
#include "../../Headers/random.h"
#include "../../Headers/entities.h"

using namespace org;

void environment::death(){
	std::list<entity*>::iterator current, currentb;
	double chances(0);
	double x(0);
	double y(0);
	double C(4);
	double difference(0);

	for (current=entities.begin(); current!=entities.end(); ++current){
		chances =0.0;
		x=(**current)(0)->getValue();
		for (currentb=entities.begin(); currentb!=entities.end(); ++currentb){
			if (currentb!=current){
				y=(**currentb)(0)->getValue();
				if(fabs(x-y)>fabs(y-x))difference = fabs(y-x);
				else difference = fabs(x-y);
				//std::cout << difference<<std::endl;
				chances +=exp(-pow(difference,2.0)/(2*pow(C,2.0)));
				//std::cout<<"c: "<<chances<<std::endl;
			}
		}
		//std::cout<<"chances: "<<chances<<std::endl;
		chances=chances * (double)capacity;
		if((*current)->death(chances)){
			current=entities.erase(current);
		}
	}
}

bool entity::death(double evFactor){
	if (maths::roll.flat(0,1)>evFactor) return false;
	else{
	delete this;
	return true;
	}

}
