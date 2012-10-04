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


	std::cout << "Evolving! (this could take some time)"<<std::endl;
	org::environment test; //Create an environment with default constructor => 2000 entities
	double done;
	unsigned int loops(3000); //Loops is the number of generations - can change safely
	for(unsigned int i(0); i<loops; i++){ //for loop that writes the progress bar
		test.tick(); //Ticks forward a generation allowing death or reproduction for all entities in test
		std::cout <<"\r|";
		done=((double)i+1)/(double)loops*20;
		for(unsigned int j(0); j<20; ++j) {
			if (j<(unsigned int)done) std::cout << "=";
			else std::cout << " ";
		}
		std::cout <<"|"<<done*5<<"%          ";
		std::cout.flush();
	}

	std::cout << std::endl;
}

