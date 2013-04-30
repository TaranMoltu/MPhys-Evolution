/*
 * entities.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua Warburton
 *  Purpose: contains all functions for entities.h except entity::death()
 */
#include "../Headers/entities.h"
#include "../Headers/random.h"


/*============================================================================
 * Constructors
 *========================================================================== */

org::height::height(const double &height, const double &sd, const double &rate1, const double &comp):
	value(height),
	standardDeviation(sd),
	rate(rate1){
	max=maths::pi; min=-maths::pi;
}

void org::environment::addEntity(org::entity* toAdd){
	entities.push_back(toAdd);
}

org::genome::genome(){
	 gene* temp = new height;
	 genes.push_back(temp);
}

org::genome::genome(org::gene* initial){
	 gene* temp = initial->clone();
	 genes.push_back(temp);
}

org::genome::genome(const org::genome &source){
	for(unsigned int i(0);i<source.getSize();++i){
		genes.push_back(source(i)->clone());
	}
}

void org::genome::addGene(org::gene* toCopy){
	 gene* temp = toCopy->clone();
	 genes.push_back(temp);
}

org::genome org::genome::operator=(const org::genome &source){
	if (this!=&source) {
		genes.clear();
		for(unsigned int i(0);i<source.getSize();++i){

			genes.push_back(source(i)->clone());
		}
	}
	return *this;
}
org::environment::environment(double cap, double c, std::string log):
		logFile(log), capacity(cap),  reach(c){}


/*============================================================================
 * Destructors
 *========================================================================== */
org::height::~height(){};

org::genome::~genome(){
	std::vector<org::gene*>::const_iterator current,begin,end;
	begin = genes.begin();
	end = genes.end();

	for (current=begin; current<end;++current){//delete all genes
		delete *current;
	}
	genes.clear();
}

org::environment::~environment(){
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
unsigned int org::genome::getSize()const{
	 return genes.size();
}


org::gene* org::genome::operator()(const unsigned int i) const{//override brackets to give a sane return
	if (i < 0 || i > genes.size() ){
			std::cout << "out of range" << std::endl;
			return NULL;
	}
	else{
		return (this->genes[i]);
	}
}

double org::height::getValue()const{
	return value;
}

const org::gene* org::height::getGenePointer()const{
	return this;
}
org::gene* org::genome::getGenePointer(unsigned i)const{
	return genes[i];
}

unsigned int org::environment::getSize()const{
	return entities.size();
}

/*============================================================================
 * tick
 *========================================================================== */
void org::environment::tick(){
	std::vector<org::entity*>::iterator current,end;

	death();
	entities.reserve(entities.size()*2);//reserve memory for more efficient resizing

	end=entities.end();
	for (current=entities.begin(); current<end; current++){
		this->addEntity((*current)->asex());
	}
	this->log();
}

/*============================================================================
 * Printing
 *========================================================================== */

std::ostream & org::operator<<(std::ostream &os, const org::gene &source){

	os << source.info();

	return os;
}

std::string org::height::info() const{
	std::stringstream out;
	out << "height: " << value << "m" <<" sd: " << standardDeviation <<" range:"<< min <<" - "<< max;
	return out.str();
}

std::ostream & org::operator<<(std::ostream &os, const org::genome &source){
	std::vector<gene*>::const_iterator current,begin,end;
	begin = source.genes.begin();
	end = source.genes.end();

	for (current=begin; current<end;++current){//print all genes!
		os << (*current)->info() << std::endl;
	}
	return os;
}
std::ostream & org::operator<<(std::ostream &os, const org::entity &source){
	os << "\n-------------------Info----------------------"<<std::endl;
	os << "Lifetime: " << source.lifetime << std::endl;
	os << "------------------Genome---------------------"<<std::endl;
	os << (genome)source;
	os << "---------------------------------------------"<<std::endl;

	return os;

}

std::string org::entity::log() const{
	std::stringstream out;
	out << genes[0]->getValue();
	return out.str();

}

void org::environment::log()const{
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

