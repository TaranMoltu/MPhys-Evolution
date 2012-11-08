/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 *  Purpose: Location for where the simulation is run. This is just
 *  the user-facing frontend, everything else is done in the headers
 */

#include "Headers/entities.h"
#include "Headers/random.h"

int main(){

	double carryingCapacity(20000);
	double standDeviation(0.01); //variation in height
	double reach(4.0);
	unsigned int loops(2000); //Loops is the number of generations - can change safely

	std::stringstream fileName;
	fileName << "k=" << carryingCapacity << ",c=" << reach << ",sigma="<< standDeviation <<",loops="<< loops <<".dat";

	std::cout.precision(3);
	std::cout << "Evolving! (this could take some time)"<<std::endl;
	org::environment test(1.0/carryingCapacity,reach,fileName.str()); //Create an environment with carrying capacity and range.
	org::entity* temp;



	for(unsigned int i(0);i<5000;i++){
		temp= new org::entity(1, org::genome(&org::height(maths::roll.flat(-maths::pi,+maths::pi),standDeviation)));
		test.addEntity(temp);
	}
	double done;

	for(unsigned int i(0); i<loops; i++){ //for loop that writes the progress bar
		test.tick(); //Ticks forward a generation allowing death or reproduction for all entities in test
		std::cout <<"\r|";
		done=((double)i+1)/(double)loops*20;
		for(unsigned int j(0); j<20; ++j) {
			if (j<(unsigned int)done) std::cout << "=";
			else std::cout << " ";
		}
		std::cout <<"|"<<done*5<<"%   | Entities:"<< test.getSize() <<"                 ";
		std::cout.flush();
	}

	std::cout << std::endl;
}

