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
	cout << "DARWIN - Program symulujacy ewolucje populacji osobnikow." << endl;
	cout << "Program uruchamiany jest z linii polecen z wykorzystaniem nastepujacych przelacznikow:" << endl;
	cout << "	-i	plik wejsciowy z populacja" << endl;
	cout << "	-o	plik wyjsciowy z populacja" << endl;
	cout << "	-w	wspolczynnik wymierania z zakresu <0, 1>" << endl;
	cout << "	-r	wspolczynnik rozmnazania z zakresu <0, 1>, ale wiekszy badz rowny wspolczynnikowi wymierania" << endl;
	cout << "	-p	liczba pokolen" << endl;
	cout << "	-k	liczba krzyzujacych sie par" << endl;
	cout << "Przykladowe wywolanie programu:" << endl;
	cout << argument << " -i wejscie.txt -o wyjscie.txt -w 0.43 -r 0.74 -p 421 -k 23" << endl;
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
				string end = "Pomoc dla uzytkownika:";
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
		string error = "Blednie podane argumenty.";
		throw error;
	}

	if (arguments[argNumber - 1] == HELP_LABEL)
	{
		string end = "Pomoc dla uzytkownika:";
		throw end;
	}

	if (argNumber != rightNumberOfArguments)
	{
		string error = "Zla liczba argumentow.";
		throw error;
	}

	if (factors.deathFactor > factors.cloneFactor)
	{
		string error = "Wspolczynnik wymierania wiekszy od wspolczynnika rozmnazania.";
		throw error;
	}

	if (factors.deathFactor > 1 || factors.deathFactor < 0)
	{
		string error = "Wspolczynnik wymierania nie nalezy do przedzialu <0, 1>.";
		throw error;
	}

	if (factors.cloneFactor > 1 || factors.cloneFactor < 0)
	{
		string error = "Wspolczynnik klonowania nie nalezy do przedzialu <0, 1>.";
		throw error;
	}

	if (factors.generationsNumber < 0)
	{
		string error = "Liczba pokolen powinna byc nieujemna.";
		throw error;
	}

	if (factors.crossingNumber < 0)
	{
		string error = "Liczba krzyzowan powinna byc nieujemna.";
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
			string error = "Wystapil blad podczas czytania argumentow.";
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
			string error = "Nie udalo sie otworzyc pliku " + dataName;
			throw error;
		}
		inputData.close();
	}
	catch (exception e)
	{
		string error = "Wystapil nieznany blad zwiazany z plikiem " + dataName;
		throw error;
	}
}

void passTheGeneration(const Factors & factors, Population & population)
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
		string error = "Wystapil problem podczas zapisu do pliku " + dataName;
		throw error;
	}
}
