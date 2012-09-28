/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 */

#include "Headers/entities.h"
#include "Headers/random.h"

//Declare constant PI
const double pi=std::acos(-1.0); //gives the maximum number of decimal places for a double

int main(){

	maths::random test;

	std::cout << "hello world"<<std::endl;
	org::entity test2;
	std::cout<< test2<<std::endl;
	org::entity* test2a= test2.asex();
	for(int i(0);i<10;i++){
		std::cout << *test2a<<std::endl;
		test2a= test2a->asex();
	}

}

