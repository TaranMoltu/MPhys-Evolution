/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 */

#include "Headers/entities.h"
#include "Headers/random.h"




int main(){


	std::cout << "Evolving! (this could take some time)"<<std::endl;
	org::environment test;
	double done;
	unsigned int loops(3000);
	for(unsigned int i(0); i<loops; i++){
		test.tick();
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

