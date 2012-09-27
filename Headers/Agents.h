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
	
		gene* clone(){
			gene* temp = new height(this->value,this->rate);
			return temp;
		}
		height(const double height=1.5, const double rate=0.0):value(height), rate(rate){}
		virtual ~height(){}
		
		virtual void mutate(){
			double mean = value;
			double sd=rate;
			double x1, x2, w, z1; //x1 and x2 are the random numbers defined in Boxmuller function
			static double z2; //Z2 is the second distributed value
			static int use_last = 0; //The box-muller function generates two values. It is more useful to save this value for the second call
			srand((unsigned)time(0)); //Seeds random numbers based on time of execution;
			if (use_last)		        
			{
				z1 = z2;
				use_last = 0;
			}
			else
			{
				do {
					double RandomNumber = (double(rand()) / double(RAND_MAX)) * (1 - 0) + 0; //Gives a random number between 0 and 1
					x1 = 2.0 * RandomNumber - 1.0;
					RandomNumber = (double(rand()) / double(RAND_MAX)) * (1 - 0) + 0; //Get a new random number between 0 and 1
					x2 = 2.0 * RandomNumber - 1.0; 
					w = x1 * x1 + x2 * x2;
				} while ( w >= 1.0 );

				w = sqrt( (-2.0 * log( w ) ) / w );
				z1 = x1 * w;
				z2 = x2 * w;
				use_last = 1;
			}

			value = ( mean + z1 * sd ); //To get any mean/sd we scale wrt sd and transform wrt mean (source: http://en.literateprograms.org/Box-Muller_transform_%28C%29)
		}
		
			
		
		
		virtual bool selection(){
			//taller is better kk.
			if(this->value > 1.5){
				return true;
			}else{
				return false;
			}
		
		}
	
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

	class agent {
	
	protected:
	
		double lifetime;
		genome props;	
	
		virtual agent* clone() const{
			return new agent(*this); 
		} 
	public:
		agent(const double lifetime=1.0, const genome props=genome()): lifetime(lifetime), props(props){
		
		}
		virtual ~agent(){}

		agent* clone(){
			agent* temp = new agent(this->lifetime, this->props);
			return temp;
		}

		agent* asex(){
			agent* temp = this->clone();
			temp->props.mutate();
			return temp;
		}
	};




}

#endif
