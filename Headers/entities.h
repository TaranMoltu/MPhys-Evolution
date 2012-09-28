#ifndef Agents
#define Agents

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>

namespace org{

class gene {
	
	friend std::ostream & operator<<(std::ostream &os, const gene &source);

	public:

		virtual gene* clone()const=0;//factory
		virtual ~gene(){};
		virtual void mutate()=0; // how does this gene mutate?
		virtual bool selection()=0; //may need to be numerical later- how is this gene selected
		virtual std::string info()const=0;
		
	
	};
	
class height : public gene{
	protected:
		double value;
		double rate; //rate of mutation

	public:
		virtual gene* clone()const;
		height(const double &height, const double &rate1);
		~height();
		virtual void mutate();
		virtual bool selection();
		virtual std::string info() const;

	};

class genome{

	friend std::ostream & operator << (std::ostream &os, const genome &source);

protected:
	std::vector<gene*> genes;

public:
	void addGene(gene* toCopy);

	genome();
	genome(const genome &source);

	~genome();

	unsigned int getSize()const;

	genome operator=(const genome &source);
	gene* operator()(const unsigned int i) const;

	void mutate();
	
	};

class entity: public genome {
	friend std::ostream & operator << (std::ostream &os, const entity &source);
	protected:

		double lifetime;


	public:
		entity(const double lifetime=1.0, const genome &genomeSource = genome()  ): genome(genomeSource), lifetime(lifetime) {}
		virtual ~entity(){}

		entity* clone() const; //factory for entities

		entity* asex(); //reproduce asexually.

};

class environment{
	protected:
		std::vector<entity*> entities;
	public:
		environment(){}
		~environment(){
			std::vector<entity*>::const_iterator current,begin,end;
			begin = entities.begin();
			end = entities.end();

			for (current=begin; current<end;++current){//delete all genes
				delete[] *current;
			}
			entities.clear();
		}
		void addEntity(entity* toAdd);

	};

std::ostream & operator<<(std::ostream &os, const gene &source);
std::ostream & operator<<(std::ostream &os, const genome &source);
std::ostream & operator<<(std::ostream &os, const entity &source);
}

#endif