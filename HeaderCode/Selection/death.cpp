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
	std::vector<entity*>::iterator current, currentb;
	double* chances = new double[getSize()];

	double x(0), y(0), normalisation(capacity/(std::sqrt(2.0*maths::pi)*reach));
	unsigned i(0), j(0);
	unsigned size(getSize());


	double difference(0);

	for (current=entities.begin(); current<entities.end(); ++current){
		if(i>=size){
			std::cout<< "("<<i<<"/"<<size<<") break!"<<std::endl;
			break;
		}
		x=(**current)(0)->getValue();
		j=0;
		for (currentb=entities.begin(); currentb<entities.end(); ++currentb){
			if (j>2000) {*(chances+i) *=(double)size/(double)j; break;} //after sampling 2000 other organisms, assume we have a representative sample
			if (currentb!=current){
				y=(**currentb)(0)->getValue();
				fabs(x-y)>maths::pi ? difference = 2.0 * maths::pi - fabs(y-x) : difference = fabs(x-y);
				//std::cout << difference<<std::endl;
				*(chances+i) +=exp(-1.0*pow(difference,2.0)/(2.0*pow(reach,2.0)));
				//std::cout <<"c: "<<*(chances+i)<<std::endl;
			}
		j++;
		}
		//std::cout<<"chances: "<<chances<<std::endl;
		*(chances+i) *=normalisation;
		i++;
	}

	i=0;
	for (current=entities.begin(); current<entities.end(); ++current){
		//std::cout<<"chances"<<i<<": "<<*(chances+i)<<std::endl;
		if((*current)->death(*(chances+i))) current=--(entities.erase(current));
		i++;
	}
	//std::cout << i <<std::endl;

	//std::fstream logStream;
	//logStream.open("chances.log", std::ios::out | std::ios::app);
	//logStream << "("<< i <<"/"<< size<<")";
	//for (unsigned int j(0); j<getSize(); ++j){
	//	if (j==0) logStream << *(chances+j);
	//	else logStream << ","<<*(chances+j);
	//}
	//
	//logStream <<std::endl;
	//logStream.close();

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
