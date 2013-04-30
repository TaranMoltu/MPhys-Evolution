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

height::height(const double &height, const double &sd, const double &rate1): value(height), standardDeviation(sd), rate(rate1) {
	max=maths::pi; min=-maths::pi;
}

void environment::addEntity(entity* toAdd){
	entities.push_front(toAdd);
}

genome::genome(){
	 gene* temp = new height;
	 genes.push_back(temp);
}

genome::genome(gene* initial){
	 gene* temp = initial->clone();
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

region region::operator=(const region &source){
	if (this!=&source) {
		start= source.start;
		end= source.end;
		modifier=source.modifier;
	}
	return *this;
}

environment::environment(double cap, double c, std::string log,const double regionStart, const double regionEnd, const double regionMod):
		logFile(log), capacity(cap),  reach(c){
	favoured=region(regionStart,regionEnd,regionMod);
		}
region::region(double start, double end, double modifier):
		start(start), end(end),modifier(modifier){}

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

environment::~environment(){
	std::list<entity*>::const_iterator current,begin,end;
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

double height::getValue()const{
	return value;
}

unsigned int environment::getSize()const{
	return entities.size();
}

/*============================================================================
 * tick
 *========================================================================== */
void environment::tick(){
	//entities.reserve(entities.size()*2);
	std::list<entity*>::iterator current,end;
		current = entities.begin();
		end = entities.end();
		entity* parent;
		entity* child;
		death();
		for (current=entities.begin(); current!=end; ++current){
			parent = (*current);
			child=parent->asex();
			this->addEntity(child);
			//std::cout<<"birth!"<<std::endl;
		}
	this->log();
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

std::string entity::log() const{
	std::stringstream out;
	out << genes[0]->getValue();
	return out.str();

}

void environment::log()const{
	std::fstream logStream;
	logStream.open(logFile.c_str(), std::ios::out | std::ios::app);
	std::list<entity*>::const_iterator current,end;
	end = entities.end();

	for (current=entities.begin(); current!=end; ++current){
		if (current==entities.begin()) logStream << (*current)->log();
		else logStream << ","<<(*current)->log();
	}

	logStream <<std::endl;
	logStream.close();
}

