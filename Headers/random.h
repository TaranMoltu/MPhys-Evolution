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

namespace maths{
	class random {

		private:
			double storedGaussian;
			bool use;

		public:

			random(): storedGaussian(0.0), use(false){
				srand((unsigned)time(0)); //Seeds the random number generator based on the time of execution
			}

			double flat(double Min, double Max);

			double gaussian(double sd, double mean);
	};
}

#endif /* RANDOM_H_ */
