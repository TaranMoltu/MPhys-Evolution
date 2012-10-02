/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 */

#include "Headers/entities.h"
#include "Headers/random.h"




int main(){


	std::ofstream file("run.dat");
	std::cout << "hello world"<<std::endl;
	org::environment test;
	for(unsigned int i(0); i<9; i++){
		std::cout << i<<std::endl;;
		test.tick();
		std::cout <<"end of "<< i<<std::endl;
	}



	file.close();

}

