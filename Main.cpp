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

	double carryingCapacity(500);
	double standDeviation(0.01); //variation in height
	double reach(4.0);
	double compatability (0.1);
	unsigned attempts(50);
	unsigned int loops(2000); //Loops is the number of generations - can change safely

	std::cout << "Carrying capacity (k): ";
	std::cin >> carryingCapacity;
	std::cout << std::endl << "standard Deviation (delta): ";
	std::cin >> standDeviation;
	std::cout << std::endl << "Competition distance (c): ";
	std::cin >> reach;
	std::cout << std::endl << "Compatability (0-->1) (q): ";
	std::cin >> compatability;
	std::cout << std::endl << "mating attempts/organism/tick (t): ";
	std::cin >> attempts;

	std::stringstream fileName;
	fileName << "k=" << carryingCapacity << ",c=" << reach << ",delta="<< standDeviation <<",q="<< compatability <<",t="<< attempts <<",loops="<< loops <<".dat";

	std::cout.precision(3);
	std::cout << "  Evolving! (this could take some time)  "<<std::endl;
	std::cout << "-----------------------------------------"<<std::endl;
	std::cout << "carrying capacity: "<< carryingCapacity <<std::endl;
	std::cout << "standard Deviation (Delta): "<< standDeviation <<std::endl;
	std::cout << "Competition distance (c): "<< reach <<std::endl;
	std::cout << "Compatability (q): "<< compatability <<std::endl;
	std::cout << "mating attempts/organism/tick (t): "<< attempts <<std::endl;
	std::cout << "-----------------------------------------"<<std::endl;
	org::environment test(1.0/carryingCapacity,reach,fileName.str()); //Create an environment with carrying capacity and range.

	org::gene* prototypeGene;
	org::entity* temp;

	for(unsigned int i(0);i<carryingCapacity/10;i++){


    prototypeGene =  new org::height(maths::roll.flat(-maths::pi,+maths::pi));
    temp= new org::entity(prototypeGene);

    test.addEntity(temp);
		delete prototypeGene;
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

