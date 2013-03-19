/*
 * death.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua Warburton
 *  Purpose: decides whether an organism dies or lives - please don't
 *  tell the university ethics committee that we are doing this by a
 *  dice roll. They probably wouldn't be impressed.
 */
#include "../../Headers/random.h"
#include "../../Headers/entities.h"

 #include <thread>

using namespace org;

void environment::deathThread(unsigned start, unsigned length, double* chances) {
	std::vector<entity*>::iterator current,begin, currentb;
	double normalisation(capacity/(std::sqrt(2.0*maths::pi)*reach));
	unsigned i(0);
	double difference(0), chance;

	begin=entities.begin()+start;

	for (current=begin; current<entities.end(); ++current){
		if (i==length) break;
		chance=0.0;

		for (currentb=entities.begin(); currentb<entities.end(); ++currentb){
			if (currentb!=current){
				difference=(*current)->competition(**currentb);
				//std::cout << difference<<std::endl;
				chance +=exp(-1.0*pow(difference,2.0)/(2.0*pow(reach,2.0)));
				//std::cout<<"c: "<<chances<<std::end;
			}
		}

		*(chances+i) =chance*normalisation;
		//std::cout<<"chances: "<<*(chances+i)<<std::endl;
		//if((*current)->death(*(chances+i))) current=--(entities.erase(current));
		i++;

	}
	//std::cout<< "thread "<< start/length <<" finished"<<std::endl;
}

void environment::death(){
	std::vector<entity*>::iterator current,end;
	double* chances = new double[getSize()];

	//--Thread maths---------------------------------------

	unsigned numThreads(8), blockSize(getSize()/numThreads);
	unsigned start, length;

	if(numThreads>1){
		std::thread threads[numThreads-1];//use main to do some work too!

		for (unsigned k = 0; k < numThreads-1; ++k) {//launch threads
			start=k*blockSize;
			try{
				threads[k] = std::thread(&org::environment::deathThread, this, start, blockSize,chances+start);
			} catch(std::exception &ex){
				std::cerr<<"failed to launch thread, reason: " <<ex.what() <<std::endl;
				exit(1);
			}
		}

		//--End thread maths--------------------------------------
		start=(numThreads-1)*blockSize;
		length=getSize()-(numThreads-1)*blockSize;
		deathThread(start,length,chances+start);

		//Join threads
		for (unsigned k = 0; k < numThreads-1; k++) {
			try{
			threads[k].join();
			} catch (std::exception &ex){
				std::cerr << "thread join fail, error:  "<< ex.what() <<std::endl;
				exit(1);
			}
		}
	}else{
		deathThread(0,getSize(),chances);
	}

	unsigned i(0);
	std::vector<entity*> survivers;
	survivers.reserve(this->getSize());
	end=entities.end();

	for (current=entities.begin(); current<end; ++current){
		//std::cout<<"chances"<<i<<": "<<*(chances+i)<<std::endl;
		if(!(*current)->death(*(chances+i))) survivers.push_back(*current);
		i++;
	}
	entities.clear();
	entities=survivers;
	survivers.clear();

	std::fstream logStream;
	logStream.open("chances.log", std::ios::out | std::ios::app);
	logStream << "("<< i <<"/"<< getSize()<<")";
	for (unsigned int j(0); j<getSize(); j++){
		if (j==0) logStream << *(chances+j);
		else logStream << ","<<*(chances+j);
		//std::cout<<*(chances+j);
	}

	logStream <<std::endl;
	logStream.close();
	try{
		delete[] chances;
	}catch(std::exception &ex){
		std::cerr << "memory cleaning fail, error: "<< ex.what() <<std::endl;
		exit(1);
	}
}

bool entity::death(double evFactor){
	if (maths::roll.flat(0.0,1.0)>evFactor) return false;
	else{
		delete this;
		return true;
	}
}
