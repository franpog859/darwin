#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include "Chromosome.h"
#include "Population.h"
#include "Darwin.h"
#include "Factors.h"

using namespace std;

void helpUser(const string & argument)
{
	cout << "DARWIN - Simple population evolution simulator." << endl;
	cout << "The program is run form the command line. I uses following switches:" << endl;
	cout << "	-i	input file with population" << endl;
	cout << "	-o	output file with population" << endl;
	cout << "	-w	deathFactor from the range <0, 1>" << endl;
	cout << "	-r	cloneFactor form the range <0, 1>, but greater than or equal to deathFactor" << endl;
	cout << "	-p	number of generations" << endl;
	cout << "	-k	number of crossing pairs" << endl;
	cout << "Example:" << endl;
	cout << argument << " -i input.txt -o output.txt -w 0.43 -r 0.74 -p 12 -k 8" << endl;
}

void readArguments(int argNumber, char ** arguments, string & inputDataName, string & outputDataName, Factors & factors)
{
	const string INPUT_LABEL = "-i";
	const string OUTPUT_LABEL = "-o";
	const string DEATH_LABEL = "-w";
	const string CLONE_LABEL = "-r";
	const string GENERATIONS_LABEL = "-p";
	const string CROSSING_LABEL = "-k";
	const string HELP_LABEL = "-h";

	const int INPUT_FLAG = 1;
	const int OUTPUT_FLAG = INPUT_FLAG << 1;
	const int DEATH_FLAG = INPUT_FLAG << 2;
	const int CLONE_FLAG = INPUT_FLAG << 3;
	const int GENERATIONS_FLAG = INPUT_FLAG << 4;
	const int CROSSING_FLAG = INPUT_FLAG << 5;

	const int rightNumberOfArguments = 13;

	const int CORRECT_RESULT = INPUT_FLAG | OUTPUT_FLAG | DEATH_FLAG | CLONE_FLAG | GENERATIONS_FLAG | CROSSING_FLAG;
	int result = 0;

	try
	{
		for (int i = 1; i < argNumber - 1; i++)
		{
			if (arguments[i] == INPUT_LABEL)
			{
				inputDataName = arguments[i + 1];
				result |= INPUT_FLAG;
			}
			if (arguments[i] == OUTPUT_LABEL)
			{
				outputDataName = arguments[i + 1];
				result |= OUTPUT_FLAG;
			}
			if (arguments[i] == DEATH_LABEL)
			{
				factors.deathFactor = atof(arguments[i + 1]);
				result |= DEATH_FLAG;
			}
			if (arguments[i] == CLONE_LABEL)
			{				
				factors.cloneFactor = atof(arguments[i + 1]);
				result |= CLONE_FLAG;
			}
			if (arguments[i] == GENERATIONS_LABEL)
			{
				factors.generationsNumber = atoi(arguments[i + 1]);          
				result |= GENERATIONS_FLAG;
			}
			if (arguments[i] == CROSSING_LABEL)
			{
				factors.crossingNumber = atoi(arguments[i + 1]);
				result |= CROSSING_FLAG;
			}
			if (arguments[i] == HELP_LABEL)
			{
				string end = "Help:";
				throw end;
			}
		}
	}
	catch (string end) 
	{
		throw end;
	}
	catch (exception e)
	{
		string error = "Wrong switches.";
		throw error;
	}

	if (arguments[argNumber - 1] == HELP_LABEL)
	{
		string end = "Help:";
		throw end;
	}

	if (argNumber != rightNumberOfArguments)
	{
		string error = "Wrong number of switches.";
		throw error;
	}

	if (factors.deathFactor > factors.cloneFactor)
	{
		string error = "deathFactor is greater than cloneFactor.";
		throw error;
	}

	if (factors.deathFactor > 1 || factors.deathFactor < 0)
	{
		string error = "deathFactor is not from th range <0, 1>.";
		throw error;
	}

	if (factors.cloneFactor > 1 || factors.cloneFactor < 0)
	{
		string error = "cloneFactor is not from th range <0, 1>.";
		throw error;
	}

	if (factors.generationsNumber < 0)
	{
		string error = "Number of generations should not be negative.";
		throw error;
	}

	if (factors.crossingNumber < 0)
	{
		string error = "Number of crossing pairs should not be negative.";
		throw error;
	}

	else
	{
		if (result == CORRECT_RESULT)
		{
			return;
		}
		else
		{
			string error = "Error with reading switches.";
			throw error;
		}
	}
}

void getInput(const string & dataName, Population & population)
{
	ifstream inputData(dataName);
	try
	{
		if (inputData)
		{
			string rawChromosome;
			while (getline(inputData, rawChromosome))
			{
				stringstream ss;
				ss << rawChromosome;
				Chromosome newChromosome;
				int data;
				while (ss >> data)
				{
					newChromosome.addToChromosome(data);
				}
				population.addPerson(newChromosome); 
			} 
		}
		else
		{
			string error = "Cannot open the file " + dataName;
			throw error;
		}
		inputData.close();
	}
	catch (exception e)
	{
		string error = "Error with the file " + dataName;
		throw error;
	}
}

void passTheGenerations(const Factors & factors, Population & population)
{
	for (int i = 0; i < factors.generationsNumber; i++)
	{
		population.crossingFunction(factors);
		population.killingFunction(factors);
		population.cloningFunction(factors);
	}
}

void saveOutput(const string & dataName, const Population & population)
{
	ofstream outputData(dataName);
	try
	{
		if (outputData)
		{
			for (int i = population.getSize() - 1; i >= 0; i--)
			{
				for (int j = population.getPersonsChromosome(i).getSize() - 1; j >= 0; j--)
				{
					outputData << setw(5) << population.getPersonsChromosome(i).getSingleChromosomeNumber(j);
				}
				outputData << endl;
			}
		}
	}
	catch (exception e)
	{
		string error = "Error with saving data to " + dataName;
		throw error;
	}
}

void clearPopulation(Population & population)
{
	//It is only to proove that there is no leaks.
	population.die();
	population.die(); //Second one is to check if everything works well.
}
