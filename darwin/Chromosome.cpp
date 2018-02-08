#include "stdafx.h"
#include "Chromosome.h"
#include <random>
#include <chrono>


Chromosome::Chromosome()
{
	head = nullptr;
	sizeValue = 0;
}

Chromosome::Chromosome(const Chromosome & model)
{
	auto pointer = model.head;
	head = nullptr;
	while (pointer)
	{
		addToChromosome(pointer->chromosomeNumber);
		pointer = pointer->nextSingleChromosomeNumberPointer;
	}
	sizeValue = model.sizeValue;
}

Chromosome::~Chromosome()
{
	deleteChromosome();
}

void Chromosome::deleteChromosome()
{
	while (head)
	{
		auto pointer = head;
		head = head->nextSingleChromosomeNumberPointer;
		delete pointer;
	}
	head = nullptr;
	sizeValue = 0;
}

void Chromosome::addToChromosome(int data)
{
	head = new SingleChromosomeNumber{ data, head };
	sizeValue++;
}

int Chromosome::getSingleChromosomeNumber(int whichNumber) const
{
	auto pointer = head;
	for (int i = 0; i < whichNumber; i++)
	{
		pointer = pointer->nextSingleChromosomeNumberPointer;
	}
	return pointer->chromosomeNumber;
}

void crossTwoChromosomes(Chromosome & firstChromosome, Chromosome & secondChromosome)
{
	if (firstChromosome.getSize() > 1 && secondChromosome.getSize() > 1)
	{
		std::default_random_engine engine;
		std::uniform_real_distribution<double> distribution;

		auto time = std::chrono::system_clock::now();
		auto interval = time.time_since_epoch();
		engine.seed(interval.count());

		int whereToCutFirstOne = 0;
		int whereToCutSecondOne = 0;

		whereToCutFirstOne = (int)(distribution(engine) * ((double)firstChromosome.getSize() - 1.0) + 1.0);
		whereToCutSecondOne = (int)(distribution(engine) * ((double)secondChromosome.getSize() - 1.0) + 1.0);

		firstChromosome.mixChromosomes(whereToCutFirstOne, secondChromosome, whereToCutSecondOne);
	}
}

void Chromosome::mixChromosomes(int whereToCutThisChromosome, Chromosome & otherChromosome, int whereToCutOtherChromosome)
{
	auto pointerAtThisChromosome1 = head;
	auto pointerAtThisChromosome2 = head;
	auto pointerAtOtherChromosome1 = otherChromosome.head;
	auto pointerAtOtherChromosome2 = otherChromosome.head;

	//It will work only if both chromosomes have more than one chromosomeNumber.
	//If not they are infertile and this function will not be called.

	pointerAtThisChromosome2 = pointerAtThisChromosome2->nextSingleChromosomeNumberPointer;
	pointerAtOtherChromosome2 = pointerAtOtherChromosome2->nextSingleChromosomeNumberPointer;

	for (int i = 0; i < whereToCutThisChromosome - 1; i++)
	{
		pointerAtThisChromosome1 = pointerAtThisChromosome1->nextSingleChromosomeNumberPointer;
		pointerAtThisChromosome2 = pointerAtThisChromosome2->nextSingleChromosomeNumberPointer;
	}

	for (int i = 0; i < whereToCutOtherChromosome - 1; i++)
	{
		pointerAtOtherChromosome1 = pointerAtOtherChromosome1->nextSingleChromosomeNumberPointer;
		pointerAtOtherChromosome2 = pointerAtOtherChromosome2->nextSingleChromosomeNumberPointer;
	}

	pointerAtThisChromosome1->nextSingleChromosomeNumberPointer = pointerAtOtherChromosome2;
	pointerAtOtherChromosome1->nextSingleChromosomeNumberPointer = pointerAtThisChromosome2;

	sizeValue = size();
	otherChromosome.sizeValue = otherChromosome.size();
}

int Chromosome::size() const 
{
	int size = 0;
	auto pointer = head;
	while (pointer)
	{
		size++;
		pointer = pointer->nextSingleChromosomeNumberPointer; 
	}
	return size;
}

int Chromosome::getSize() const
{
	return sizeValue;
}