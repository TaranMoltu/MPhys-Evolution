/*
 * entities.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */
#include "../Headers/entities.h"
#include "../Headers/random.h"
using namespace org;


/*============================================================================
 * Constructors
 *========================================================================== */

height::height(const double &height, const double &sd, const double &rate1): value(height), standardDeviation(sd), rate(rate1) {
	max=maths::pi; min=-maths::pi;
}

void environment::addEntity(entity* toAdd){
	entities.push_back(toAdd);
}

genome::genome(){
	 gene* temp = new height;
	 genes.push_back(temp);
}

genome::genome(const genome &source){
	for(unsigned int i(0);i<source.getSize();++i){
		genes.push_back(source(i)->clone());
	}
}

void genome::addGene(gene* toCopy){
	 gene* temp = toCopy->clone();
	 genes.push_back(temp);
}

genome genome::operator=(const genome &source){
	if (this!=&source) {
		genes.clear();
		for(unsigned int i(0);i<source.getSize();++i){

			genes.push_back(source(i)->clone());
		}
	}
	return *this;
}


/*============================================================================
 * Destructors
 *========================================================================== */
height::~height(){};

genome::~genome(){
	std::vector<gene*>::const_iterator current,begin,end;
	begin = genes.begin();
	end = genes.end();

	for (current=begin; current<end;++current){//delete all genes
		delete *current;
	}
	genes.clear();
}

/*============================================================================
 * Accesors
 *========================================================================== */
unsigned int genome::getSize()const{
	 return genes.size();
}


gene* genome::operator()(const unsigned int i) const{//override brackets to give a sane return
	if (i < 0 || i > genes.size() ){
			std::cout << "out of range" << std::endl;
			return NULL;
	}
	else{
		return (this->genes[i]);
	}
}

/*============================================================================
 * Printing
 *========================================================================== */

std::ostream & org::operator<<(std::ostream &os, const gene &source){

	os << source.info();

	return os;
}

std::string height::info() const{
	std::stringstream out;
	out << "height: " << value << "m" <<" sd: " << standardDeviation <<" range:"<< min <<" - "<< max;
	return out.str();
}

std::ostream & org::operator<<(std::ostream &os, const genome &source){
	std::vector<gene*>::const_iterator current,begin,end;
	begin = source.genes.begin();
	end = source.genes.end();

	for (current=begin; current<end;++current){//print all genes!
		os << (*current)->info() << std::endl;
	}
	return os;
}
std::ostream & org::operator<<(std::ostream &os, const entity &source){
	os << "\n-------------------Info----------------------"<<std::endl;
	os << "Lifetime: " << source.lifetime << std::endl;
	os << "------------------Genome---------------------"<<std::endl;
	os << (genome)source;
	os << "---------------------------------------------"<<std::endl;

	return os;

}


