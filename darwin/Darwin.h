#ifndef DARWIN_H
#define DARWIN_H

#include "Population.h"
#include "Factors.h"
#include <string>
using namespace std;

void helpUser(const string & argument);

void readArguments(int argNumber, char ** arguments, string & inputDataName, string & outputDataName, Factors & factors);

void getInput(const string & dataName, Population & population);

void passTheGeneration(const Factors & factors, Population & population);

void saveOutput(const string & dataName, const Population & population);

#endif

