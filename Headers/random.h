/*
 * random.h
 *
 *  Created on: 27 Sep 2012
 *      Author: Joshua
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include<cstdlib> //Use for random numbers
#include<ctime> //Use to seed pseudorandom numbers
#include<cmath>

namespace maths{
	const double pi=std::acos(-1.0); //gives the maximum number of decimal places for a double
	class random {

		private:
			double storedGaussian;
			bool use;

		public:

			random(): storedGaussian(0.0), use(false){
				srand((unsigned)time(0)); //Seeds the random number generator based on the time of execution
			}

			double flat(double Min, double Max);
			int flat(int Min, int Max);
			unsigned bit();

			double gaussian(double sd, double mean);
	};
	
	extern random roll;
}

#endif /* RANDOM_H_ */
