#ifndef FITFUNCTION_H
#define FITFUNCTION_H

#include "Chromosome.h" 

class FitFunction
{
public:
	double getFitness(const Chromosome & chromosome); //Person with average number around n x 100 has the best fitness.

};

#endif 