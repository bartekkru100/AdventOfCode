#pragma once

#include <string>
#include <iostream>
#include <list>
#include "Symbol.h"

class Symbol;

class Number
{
public:
	int row = 0;
	int pos = 0;
	int value = 1;
	bool isPart = false;
	Number(int row, int pos, int value);
	int length();
	void print();
	bool isAdjacent(std::list<Symbol>& symbolList);
};