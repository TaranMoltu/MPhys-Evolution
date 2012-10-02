/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 */

#include "Headers/entities.h"
#include "Headers/random.h"

#include <fstream>


int main(){


	std::ofstream file("run.dat");
	std::cout << "hello world"<<std::endl;
	org::entity test2;
	std::cout<< test2<<std::endl;
	org::entity* test2a= test2.asex();
	for(int i(0);i<10;i++){
		file << test2a->log() <<",";
		test2a= test2a->asex();
	}




	file.close();

}

