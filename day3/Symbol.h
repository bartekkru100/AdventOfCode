#pragma once

#include <string>
#include <iostream>
#include <list>
#include "Number.h"

class Number;

class Symbol
{
public:
	int row = 0;
	int pos = 0;
	char value = '*';
	bool isGear = false;
	int gearRatio = 1;
	std::list<Number*> adjacentParts;
	Symbol(int row, int pos, char value);
	void print();
	bool isAdjacent(std::list<Number>& numberList);
};
