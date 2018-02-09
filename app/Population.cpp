#include "stdafx.h"
#include "Population.h"
#include "Factors.h"
#include "FitFunction.h"
#include <random>
#include <chrono>


Population::Population()
{
	head = nullptr;
	sizeValue = 0;
}

Population::Population(const Population & model)
{
	auto pointer = model.head;
	head = nullptr;
	while (pointer)
	{
		addPerson(pointer->chromosome);
		pointer = pointer->nextPerson;
	}
	sizeValue = model.sizeValue;
}

Population::~Population()
{
	die();
}

void Population::die()
{
	while (head)
	{
		auto pointer = head;
		head = head->nextPerson;
		delete pointer;
	}
	head = nullptr;
	sizeValue = 0;
}

void Population::addPerson(const Chromosome & chromosome)
{
	head = new Person{ chromosome , head };
	sizeValue++;
}

Chromosome Population::getPersonsChromosome(int whichPerson) const
{
	auto pointer = head;
	for (int i = 0; i < whichPerson; i++)
	{
		pointer = pointer->nextPerson;
	}
	return pointer->chromosome;
}

void Population::crossingFunction(const Factors & factors)
{
	if (head)
	{
		std::default_random_engine engine;
		std::uniform_real_distribution<double> distribution;

		auto time = std::chrono::system_clock::now();
		auto interval = time.time_since_epoch();
		engine.seed(interval.count());

		int firstToCross = 0;
		int secondToCross = 0;
		for (int i = 0; i < factors.crossingNumber; i++)
		{
			firstToCross = (int)(distribution(engine) * ((double)this->getSize()));
			secondToCross = (int)(distribution(engine) * ((double)this->getSize()));

			//If someone is infertile and try to reproduce, nothing happen. Real world.
			if (this->getPersonsChromosome(firstToCross).getSize() > 1 &&
				this->getPersonsChromosome(secondToCross).getSize() > 1)
			{
				this->addTheirBabies(firstToCross, secondToCross);
			}
		}
	}
}

void Population::addTheirBabies(int firstPerson, int secondPerson)
{
	Chromosome firstBaby = this->getPersonsChromosome(firstPerson);
	Chromosome secondBaby = this->getPersonsChromosome(secondPerson);

	crossTwoChromosomes(firstBaby, secondBaby);

	this->addPerson(firstBaby);
	this->addPerson(secondBaby);
}

void Population::killingFunction(const Factors & factors)
{
	if (head)
	{
		FitFunction fitFunction;
		for (int i = 0; i < this->getSize(); i++)
		{
			if (factors.deathFactor > fitFunction.getFitness(this->getPersonsChromosome(i)))
			{
				this->killPerson(i);
				i--;
			}
		}
	}
}

void Population::killPerson(int whichPerson)
{
	if (head)
	{
		if (whichPerson == 0)
		{
			auto deadPerson = head;
			head = head->nextPerson;
			delete deadPerson;
		}
		else
		{
			auto pointer = head;
			for (int i = 0; i < whichPerson - 1; i++)
			{
				pointer = pointer->nextPerson;
			}
			auto deadPerson = pointer->nextPerson;
			pointer->nextPerson = deadPerson->nextPerson;
			delete deadPerson;
		}
		sizeValue--;
	}
}

void Population::cloningFunction(const Factors & factors)
{
	if (head) 
	{
		FitFunction fitFunction;
		for (int i = 0; i < this->getSize(); i++)
		{
			if (factors.cloneFactor < fitFunction.getFitness(this->getPersonsChromosome(i)))
			{
				this->addPerson(this->getPersonsChromosome(i));
				i++;
			}
		}
	}
}

int Population::getSize() const
{
	return sizeValue;
}