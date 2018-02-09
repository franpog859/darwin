#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome 
{
private: 
	struct SingleChromosomeNumber
	{
		int chromosomeNumber;

		SingleChromosomeNumber * nextSingleChromosomeNumberPointer;
	};

	SingleChromosomeNumber * head;

	int sizeValue;

	int size() const;

public:
	Chromosome();

	Chromosome(const Chromosome & model);

	~Chromosome();

	void deleteChromosome();

	void addToChromosome(int data);

	int getSingleChromosomeNumber(int whichNumber) const;
	
	void mixChromosomes(int whereToCutThisChromosome, Chromosome & otherChromosome, int whereToCutOtherChromosome);

	int getSize() const;

	Chromosome & operator = (const Chromosome & right) = delete;
};

void crossTwoChromosomes(Chromosome & firstChromosome, Chromosome & secondChromosome);

#endif
