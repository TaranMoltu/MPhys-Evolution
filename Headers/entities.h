#ifndef Agents
#define Agents

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>

namespace org{

class gene {
	
	public:

		virtual gene* clone()=0;//factory
		virtual ~gene(){}
		virtual void mutate()=0; // how does this gene mutate?
		virtual bool selection()=0; //may need to be numerical later- how is this gene selected
		
	
	};
	
class height : public gene{
	protected:
		double value;
		double rate; //rate of mutation

	public:
		gene* clone();
		height(const double height=1.5, const double rate=0.0):value(height), rate(rate){}
		virtual ~height(){}
		void mutate();
		bool selection();

	};

class genome{
	 public:
	 std::vector<gene*> genes;

	 void addGene(gene* toCopy){
		 gene* temp = toCopy->clone();
		 genes.push_back(temp);
	 }

	 genome(){
		 gene* temp = new height(1.5,0.0);
		 genes.push_back(temp);
	 }

	 ~genome(){
		std::vector<gene*>::const_iterator current,begin,end;
		begin = genes.begin();
		end = genes.end();

		for (current=begin; current<end;++current){//delete all genes
			delete[] *current;
		}
		genes.clear();
	 }

	 unsigned int getSize()const{
		 return genes.size();
	 }

	genome operator=(const genome &source){
		if (this!=&source) {
			genes.clear();
			for(unsigned int i(0);i<source.getSize();++i){

				genes.push_back(source(i)->clone());
			}
		}
		return *this;
	}

	 //genome(genome toCopy){


	 //}



	 gene* operator()(const unsigned int i) const{//override brackets to give a sane return
	 	if (i == 0 || i > genes.size() ){
	 			std::cout << "out of range" << std::endl;
	 			return NULL;
	 	}
	 	else{
	 		return (this->genes[i]);
	 	}
	 }

	 void mutate(){
		 std::vector<gene*>::const_iterator current,begin,end;
		begin = genes.begin();
		end = genes.end();

		for (current=begin; current<end;++current){//delete all genes
			(*current)->mutate();
		}
	 }
	
	};

class entity {
	
	protected:
	
		double lifetime;
		genome props;	
	
		virtual entity* clone() const{
			return new entity(*this);
		} 
	public:
		entity(const double lifetime=1.0, const genome props=genome()): lifetime(lifetime), props(props){}
		virtual ~entity(){}

		entity* clone();

		entity* asex();

	};






	class environment{
	protected:
		std::vector<entity> entities;
	public:

	};
}

#endif
