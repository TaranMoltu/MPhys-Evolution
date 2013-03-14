/*
 * entities.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua Warburton
 *  Purpose: contains all functions for entities.h except entity::death()
 */
#include "../Headers/entities.h"
#include "../Headers/random.h"
#include<bitset>


/*============================================================================
 * Constructors
 *========================================================================== */

org::height::height(const genome* genome){
	unsigned numberOfSites(2);
	unsigned sites[2]={1,2};

	value =0.0;
	double random;
	for(unsigned i(0); i<numberOfSites; i++){
		std::cout <<"loopy"<< i << std::endl;
		random =maths::roll.gaussian(0.1,0.2);
		std::cout <<"random"<< i << std::endl;
		value+=(*genome)(sites[i])*random;
	}

}

void org::environment::addEntity(entity* toAdd){
	entities.push_back(toAdd);
}

org::genome::genome(){
	 base2Genome.push_back(0x0);
	 size=1;
}

org::genome::genome(const genome* source){
	bool create(0);
	if (source==NULL){source = new genome(); create =1;}
	size=source->getSize();
	unsigned bytes;
	size % 8>0 ? bytes=size/8+1:bytes=size/8;
	base2Genome.reserve(bytes);
	for(unsigned int i(0);i<bytes;++i){
		base2Genome.push_back(source->base2Genome[i]);
	}
	if (create){delete source;}
}

org::genome::genome(unsigned length){
	size=length;
	unsigned bytes;
	length % 8>0 ? bytes=length/8+1:bytes=length/8;
	for(unsigned i(0);i<bytes;++i){
		base2Genome.push_back(0x0);
		for (unsigned j(0);j<8;++j){
			base2Genome[i]= base2Genome[i] ^ ((char)maths::roll.bit()<<j);

		}
	}
}

org::genome org::genome::operator=(const genome &source){
	if (this!=&source) {
		base2Genome.clear();
		unsigned bytes;
		size=source.getSize();
		size % 8>0 ? bytes=size/8+1:bytes=size/8;
		base2Genome.reserve(bytes);
		for(unsigned int i(0);i<bytes;++i){

			base2Genome.push_back(source(i));
		}
	}
	return *this;
}

org::entity::entity(const double pos,const genome* prototype) : genome(prototype), position(pos) {
	gene* proto(new height(this));
	genes.push_back(proto);
}

org::environment::environment(double cap, double c, std::string log):
		logFile(log), capacity(1.0/cap),  reach(c), minPosition(-maths::pi),maxPosition(maths::pi){
		}


/*============================================================================
 * Destructors
 *========================================================================== */

org::genome::~genome(){

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
	 return size;
}

double org::entity::getPosition()const{
	return position;
}


int org::genome::operator()(const unsigned int i) const{//override brackets to give a sane return
	if (i < 0 || i > size ){
			std::cerr << "out of range" << std::endl;
			return -1;
	}
	else {
		unsigned byte=i/8;
		return base2Genome[byte] & 1<<(i-byte*8);
	}
}


unsigned int org::environment::getSize()const{
	return entities.size();
}

org::genome org::entity::getGenome() const{
	return *this;
}

char org::genome::getGenomeByte(unsigned i) const{
	if (i < 0 || i > base2Genome.size() ){
		std::cerr << "out of range" << std::endl;
		return -1;
	}
	else {
		return base2Genome[i];
	}
}

double org::height::getValue()const{
	return value;
}

/*============================================================================
 * tick
 *========================================================================== */
void org::environment::tick(){

	std::vector<entity*>::iterator current,end;
	try{
		death();
		current = entities.begin();
	}catch(const std::exception &e){std::cout << e.what()<<std::endl;}
		entities.reserve(entities.size()*2);
		end=entities.end();
		for (current=entities.begin(); current<end; current++){
			try{
				this->addEntity((*current)->asex());
			}catch(const std::exception &e){std::cout << e.what()<<std::endl;}
		}
	this->log();

}
/*============================================================================
 * Printing
 *========================================================================== */


std::string org::height::info()const{
	std::stringstream out;
	out << "[height " << this->getValue() << "]";
	return out.str();
}
std::ostream & org::operator<<(std::ostream &os, const gene &source){

	os << source.info();

	return os;
}


std::ostream & org::operator<<(std::ostream &os, const genome &source){
	std::bitset<8> x;
	std::vector<char>::const_iterator current,begin,end;
	begin = source.base2Genome.begin();
	end = source.base2Genome.end();

	for (current=begin; current<end;++current){//print all genes!
		x=(*current);
		os << x;
	}
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

std::string org::entity::log() const{
	std::stringstream out;
	std::bitset<8> x;
	//out << "{";
	std::vector<char>::const_iterator current,begin,end;
	begin = base2Genome.begin();
	end = base2Genome.end();

	//for (current=begin; current<end;++current){//print ALL the genes!
		x=base2Genome[0];
		out << x;
		//std::cout<<x;
	//}

	//out <<"}";
	//out << position;
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

