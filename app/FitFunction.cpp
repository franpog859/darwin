#include "stdafx.h"
#include <math.h>
#include "Chromosome.h"
#include "Factors.h"
#include "FitFunction.h"

double FitFunction::getFitness(const Chromosome & chromosome)
{
	if (chromosome.getSize() == 0)
	{
		return 0;
	}

	double fitness = 0;
	for (int i = 0; i < chromosome.getSize(); i++)
	{
		fitness += (double)chromosome.getSingleChromosomeNumber(i);
	}
	fitness = fitness / (double)chromosome.getSize();
	fitness = fmod(fitness, 100) / 100; 
	fitness = (fitness - 0.5) * 2.0; //fitness value belongs to <-1, 1>
	if (fitness < 0)
	{
		fitness = fitness - 2.0 * fitness; //fitness value belongs to (0, 1>
	}
	return fitness;
}