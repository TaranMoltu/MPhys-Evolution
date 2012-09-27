/*
 * Main.cpp
 *
 *  Created on: 25 Sep 2012
 *      Author: Joshua Warburton
 */

#include "Headers/entities.h"
#include "Headers/random.h"
#include<iostream> //Use to output to console

//Declare constant PI
const double pi=std::acos(-1.0); //gives the maximum number of decimal places for a double

int main(){

	maths::random test;

	std::cout << "hello world"<<std::endl;
	for(unsigned int i(0);i<20;i++){
	std::cout <<test.flat(-1*pi, pi)<<std::endl;
	}
}

