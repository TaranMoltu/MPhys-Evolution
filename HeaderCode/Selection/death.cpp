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
	double normalisation(capacity/(std::sqrt(2.0*maths::pi)*reach));
	double* chances = new double[getSize()];
	unsigned int i(0);
	unsigned int size(getSize());


	double difference(0);

	for (current=entities.begin(); current!=entities.end(); ++current){
		if(i>=size){
			std::cout<< "("<<i<<"/"<<size<<") break!"<<std::endl;
			break;
		}
		for (currentb=entities.begin(); currentb!=entities.end(); ++currentb){
			if (currentb!=current){
				difference=(*current)->distance(**currentb);
				//std::cout << difference<<std::endl;
				*(chances+i) +=exp(-1.0*pow(difference,2.0)/(2.0*pow(reach,2.0)));
				//std::cout<<"c: "<<chances<<std::end;
			}
		}

		*(chances+i) *=normalisation;
		//std::cout<<"chances: "<<*(chances+i)<<std::endl;
		if((*current)->death(*(chances+i))){
			current=--(entities.erase(current));
		}
		i++;

	}

	std::fstream logStream;
	logStream.open("chances.log", std::ios::out | std::ios::app);
	logStream << "("<< i <<"/"<< size<<")";
	for (unsigned int j(0); j<getSize(); ++j){
		if (j==0) logStream << *(chances+j);
		else logStream << ","<<*(chances+j);
	}

	logStream <<std::endl;
	logStream.close();

	delete[] chances;
}

/*
void environment::death(){
	std::list<entity*>::iterator current;

	unsigned int size(getSize());

	double difference(0);

	for (current=entities.begin(); current!=entities.end(); ++current){

		if((*current)->death(size*capacity)){
			current=--(entities.erase(current));
		}

	}

}
*/
bool entity::death(double evFactor){
	if (maths::roll.flat(0.0,1.0)>evFactor) return false;
	else{
	delete this;
	return true;
	}

}
