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
	clock_t begin=clock();
	double carryingCapacity(1000);
	double reach(16.0);
	unsigned genomeSize(8);
	unsigned int loops(2000); //Loops is the number of generations - can change safely

	std::cout << "Carrying capacity (k): ";
	std::cin >> carryingCapacity;
	std::cout << std::endl << "Genome Size: ";
	std::cin >> genomeSize;
	std::cout << std::endl << "Competition distance (c): ";
	std::cin >> reach;

	std::stringstream fileName;
	fileName << "k=" << carryingCapacity << ",c=" << reach << ",genome size="<<genomeSize<<",loops="<< loops <<".dat";

	std::cout.precision(3);
	std::cout << "  Evolving! (this could take some time)  "<<std::endl;
	std::cout << "-----------------------------------------"<<std::endl;
	std::cout << "carrying capacity: "<< carryingCapacity <<std::endl;
	std::cout << "Competition distance (c): "<< reach <<std::endl;
	std::cout << "Genome Size: "<< genomeSize <<std::endl;
	std::cout << "-----------------------------------------"<<std::endl;


	org::environment test(carryingCapacity,reach,fileName.str()); //Create an environment with carrying capacity and range.
	org::entity* temp;
	org::genome* prototype;

	for(unsigned int i(0);i<100;i++){
		prototype=new org::genome(genomeSize);
		temp= new org::entity(0,prototype);
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
	std::cout <<"time taken: "<< (clock()-begin)/CLOCKS_PER_SEC <<" seconds"<< std::endl;
}

