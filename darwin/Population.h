#ifndef POPULATION_H
#define POPULATION_H

#include "Chromosome.h"
#include "Factors.h"

class Population 
{
private:
	struct Person
	{
		Chromosome chromosome;

		Person * nextPerson;
	};

	Person * head;

	int sizeValue;

	void addTheirBabies(int firstPerson, int secondPerson);

	void killPerson(int whichPerson);

public:
	Population();

	Population(const Population & model);

	~Population();

	void die();

	void addPerson(const Chromosome & chromosome);

	Chromosome getPersonsChromosome(int whichPerson) const;

	void crossingFunction(const Factors & factors);

	void killingFunction(const Factors & factors); 

	void cloningFunction(const Factors & factors);

	int getSize() const;

	Population & operator = (const Population & right) = delete; 
};

#endif