#include "stdafx.h"
#include <string>
#include <iostream>
#include "Factors.h"
#include "Population.h"
#include "Darwin.h"
using namespace std;

int main(int argNumber, char ** arguments)
{
	try
	{
		string inputDataName, outputDataName;
		Factors factors;
		Population population;

		readArguments(argNumber, arguments, inputDataName, outputDataName, factors);
		getInput(inputDataName, population);
		
		passTheGenerations(factors, population);

		saveOutput(outputDataName, population);
		
		population.die();
		population.die(); //Second one is to check if everything works well.

		cout << "Program zakonczony pomyslnie." << endl;
	}
	catch (string & e)
	{
		cerr << e << endl;
		helpUser(arguments[0]);
	}
	catch (exception & e)
	{
		cerr << "Wystapil nieznany blad." << endl;
		helpUser(arguments[0]);
	}
	
    return 0;
}