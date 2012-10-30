#ifndef Agents
#define Agents

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<cmath>
#include<fstream>

namespace org{

class gene { //gene is an abstract base class for an organisms genes
	
	friend std::ostream & operator<<(std::ostream &os, const gene &source); //overloads <<operator

	public:

		virtual gene* clone()const=0;//factory
		virtual ~gene(){}; //destructor
		virtual void mutate()=0; // how does this gene mutate?
		virtual bool selection()=0; //may need to be numerical later- how is this gene selected
		virtual std::string info()const=0; //function for returning key details on an organism
		virtual double getValue() const=0; //returns genes value eg returns height value for height etc
		
	
	};
	
class height : public gene{ //height is an implementation of gene
	protected:
		double value; //how tall organism is
		double standardDeviation; //for purpose of mutation function
		double min,max; //range of possible values
		double rate; //rate of mutation

	public:
		virtual gene* clone()const;
		height(const double &height=1.0, const double &sd=0.001, const double &rate1=0.01);
		~height();
		virtual void mutate();
		virtual bool selection();
		virtual std::string info() const;

		virtual double getValue() const;

	};

class genome{ //genome is a collection of all the genes an organism has rather like DNA

	friend std::ostream & operator << (std::ostream &os, const genome &source);

protected:
	std::vector<gene*> genes;

public:
	void addGene(gene* toCopy);

	genome();
	genome(gene* initial);
	genome(const genome &source);

	~genome();

	unsigned int getSize()const;

	genome operator=(const genome &source);
	gene* operator()(const unsigned int i) const;

	void mutate();
	
	};

class entity: public genome { //An organism which is made up of genomes. Derivation means genome is implied rather than needing to be declared in protected
	friend std::ostream & operator << (std::ostream &os, const entity &source);
	protected:

		double lifetime;


	public:
		entity(const double lifetime=1.0, const genome &genomeSource = genome()  ): genome(genomeSource), lifetime(lifetime) {}
		virtual ~entity(){}

		std::string log() const; //outputs information on a gene

		entity* clone() const; //factory for entities

		entity* asex(); //reproduce asexually.

		bool death(double evFactor); //decides whether or not the entity of mail will elate above death

};

class environment{ //collection of entities
	protected:
		std::list<entity*> entities;
		std::string logFile;
		double capacity;
		double reach; //c

	public:
		environment(double cap=1.0/100.0, double c=0.9, std::string log="log.dat");
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
