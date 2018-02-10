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
		
		clearPopulation(population);

		cout << "Program finished correctly." << endl;
	}
	catch (string & e)
	{
		cerr << e << endl;
		helpUser(arguments[0]);
	}
	catch (exception & e)
	{
		cerr << "Unknown error." << endl;
		helpUser(arguments[0]);
	}
	
    return 0;
}