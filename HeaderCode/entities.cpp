/*
 * entities.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua Warburton
 *  Purpose: contains all functions for entities.h except entity::death()
 */
#include "../Headers/entities.h"
#include "../Headers/random.h"
using namespace org;


/*============================================================================
 * Constructors
 *========================================================================== */

/*height::height(const double &height, const double &sd, const double &rate1): value(height), standardDeviation(sd), rate(rate1) {
	max=maths::pi; min=-maths::pi;
}*/

void environment::addEntity(entity* toAdd){
	entities.push_back(toAdd);
}

genome::genome(){
	 base2Genome.push_back(1);
}

genome::genome(const genome &source){
	base2Genome.reserve(source.getSize());
	for(unsigned int i(0);i<source.getSize();++i){
		base2Genome.push_back(source(i));
	}
}

genome::genome(unsigned length){
	base2Genome.reserve(length);
	for(unsigned i(0);i<length;++i){
		base2Genome.push_back(maths::roll.bit());
	}
}

genome genome::operator=(const genome &source){
	if (this!=&source) {
		base2Genome.clear();
		base2Genome.reserve(source.getSize());
		for(unsigned int i(0);i<source.getSize();++i){

			base2Genome.push_back(source(i));
		}
	}
	return *this;
}
environment::environment(double cap, double c, std::string log):
		logFile(log), capacity(1.0/cap),  reach(c), minPosition(-maths::pi),maxPosition(maths::pi){
		}


/*============================================================================
 * Destructors
 *========================================================================== */
//height::~height(){};

genome::~genome(){

}

environment::~environment(){
	std::vector<entity*>::const_iterator current,begin,end;
	end = entities.end();

	for (current=entities.begin(); current!=end;++current){//delete all genes
		delete *current;
	}
	entities.clear();
}

/*============================================================================
 * Accesors
 *========================================================================== */
unsigned int genome::getSize()const{
	 return base2Genome.size();
}

double entity::getPosition()const{
	return position;
}


int genome::operator()(const unsigned int i) const{//override brackets to give a sane return
	if (i < 0 || i > base2Genome.size() ){
			std::cout << "out of range" << std::endl;
			return -1;
	}
	else{
		return (this->base2Genome[i]);
	}
}

/*double height::getValue()const{
	return value;
*/

unsigned int environment::getSize()const{
	return entities.size();
}

genome entity::getGenome() const{
	return *this;
}

/*============================================================================
 * tick
 *========================================================================== */
void environment::tick(){

	std::vector<entity*>::iterator current,end;
		death();
		current = entities.begin();
		end = entities.end();
		entities.reserve(entities.size()*2);
		int i(0);
		this->log();
		for (current=entities.begin(); current<end; current++){
			this->addEntity((*current)->asex());
			//std::cout<<"birth!"<<std::endl;
			i++;
		}

}
/*============================================================================
 * Printing
 *========================================================================== */

std::ostream & org::operator<<(std::ostream &os, const gene &source){

	os << source.info();

	return os;
}


std::ostream & org::operator<<(std::ostream &os, const genome &source){
	std::vector<int>::const_iterator current,begin,end;
	begin = source.base2Genome.begin();
	end = source.base2Genome.end();

	for (current=begin; current<end;++current){//print all genes!
		os << (*current);
	}
	os << std::endl;
	return os;
}
std::ostream & org::operator<<(std::ostream &os, const entity &source){
	os << "\n-------------------Info----------------------"<<std::endl;
	os << "Position: " << source.position << std::endl;
	os << "------------------Genome---------------------"<<std::endl;
	os << (genome)source;
	os << "---------------------------------------------"<<std::endl;

	return os;

}

std::string entity::log() const{
	std::stringstream out;
	//out << "{";
	std::vector<int>::const_iterator current,begin,end;
	begin = base2Genome.begin();
	end = base2Genome.end();

	for (current=begin; current<end;++current){//print ALL the genes!
		out << (*current);
	}

	//out <<"}";
	//out << position;
	return out.str();

}

void environment::log()const{
	std::fstream logStream;
	logStream.open(logFile.c_str(), std::ios::out | std::ios::app);
	std::vector<entity*>::const_iterator current,end;
	end = entities.end();

	for (current=entities.begin(); current<end; ++current){
		if (current==entities.begin()) logStream << (*current)->log();
		else logStream << ","<<(*current)->log();
	}

	logStream <<std::endl;
	logStream.close();
}

