/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 *  Purpose: Location for where the simulation is run. This is just
 *  the user-facing frontend, everything else is done in the headers
 */

#include "Headers/entities.h"

int main(){

	std::cout.precision(3);
	std::cout << "Evolving! (this could take some time)"<<std::endl;
	org::environment test(10.0,1.0); //Create an environment with carrying capacity and range.
	org::entity* temp;
	org::genome* prototype;
	//double standDeviation(0.01); //variation in height


	for(unsigned int i(0);i<10;i++){
		prototype=new org::genome(8);
		temp= new org::entity(0,*prototype);
		test.addEntity(temp);
	}
	double done;
	unsigned int loops(1000); //Loops is the number of generations - can change safely
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

