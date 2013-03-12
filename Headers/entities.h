#ifndef Agents
#define Agents

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<cmath>
#include<fstream>
#include "random.h"

namespace org{

class gene;
class genome;
class environment;

class gene { //gene is an abstract base class for an organisms genes
	
	friend std::ostream & operator<<(std::ostream &os, const gene &source); //overloads <<operator

	public:

		virtual ~gene(){}; //destructor
		virtual bool selection()=0; //may need to be numerical later- how is this gene selected
		virtual std::string info()const=0; //function for returning key details on an organism
		virtual double getValue() const=0; //returns genes value eg returns height value for height etc
		
	
	};
class height : public gene {

	private:
		double value;

	public:
		height(const genome* genome);
		~height(){};
		bool selection();
		std::string info()const;
		double getValue()const;

};
	

class genome{ //genome is a collection of all the genes an organism has rather like DNA

	friend std::ostream & operator << (std::ostream &os, const genome &source);

protected:
	std::vector<char> base2Genome;
	unsigned size;

public:

	genome();
	genome(const unsigned length);
	genome(const genome* source);

	~genome();

	unsigned getSize()const;

	genome operator=(const genome &source);
	int operator()(const unsigned int i) const;
	char getGenomeByte(unsigned i)const;

	void mutatePoint(int position=-1);
	
	unsigned distance(genome &compare) const;

	};

class entity: public genome { //An organism which is made up of genomes. Derivation means genome is implied rather than needing to be declared in protected
	friend std::ostream & operator << (std::ostream &os, const entity &source);
	protected:

		double position;

	public:
		entity(const double pos=0.0,const genome* prototype=NULL): genome(prototype), position(pos) {}
		virtual ~entity(){}

		std::string log() const; //outputs information on a gene
		double getPosition() const;
		genome getGenome()const;

		entity* clone() const; //factory for entities

		entity* asex(); //reproduce asexually.

		bool death(double evFactor); //decides whether or not the entity of mail will elate above death
		unsigned distance(entity &compare) const;

};

class environment{ //collection of entities
	private:
		void deathThread(unsigned start, unsigned length, double* chances);
	protected:
		std::vector<entity*> entities;
		std::string logFile;
		double capacity;
		double reach; //c
		double minPosition;
		double maxPosition;

	public:
		environment(double cap=100.0, double c=0.9, std::string log="log.dat");
		~environment();
		void addEntity(entity* toAdd);

		void tick(); //the time is going, ticking on and on, everybody's rushing. Note by rushing I mean either dying or evolving
		void log()const; //outputs data on gene
		void death(); //decides whether organism dies or not due to roll of die - not approved by ethics committee

		unsigned int getSize()const;

	};

std::ostream & operator<<(std::ostream &os, const gene &source);
std::ostream & operator<<(std::ostream &os, const genome &source);
std::ostream & operator<<(std::ostream &os, const entity &source);
}

#endif
