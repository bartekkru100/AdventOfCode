#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "Number.h"
#include "Symbol.h"

int main(int argc, char* argv[])
{
	std::fstream file("input.txt");
	if (!file.is_open())
	{
		std::cout << "Can't open file" << std::endl;
		return 1;
	}

	std::vector<std::string> schematic;
	std::string line;
	while (getline(file, line))
	{
		schematic.push_back(line);
		std::cout << schematic.back() << '\n';
	}

	int rows = schematic.size();
	int columns = schematic.back().length();
	std::list<Symbol> symbolList;
	std::list<Number> numberList;

	for (int i = 0; i < rows; i++)
	{
		int pos = 0;
		bool canFind = true;
		while (pos < columns)
		{
			pos = schematic[i].find_first_not_of('.', pos);
			if (pos == -1)break;
			if (isdigit(schematic[i][pos]))
			{
				numberList.push_back(Number(i, pos, atoi(&schematic[i][pos])));
				pos += numberList.back().length();
				numberList.back().print();
			}
			else
			{
				symbolList.push_back(Symbol(i, pos, schematic[i][pos]));
				pos += 1;
				symbolList.back().print();
			}
		}
	}

	int sumParts = 0;

	for (Number number : numberList)
	{
		if (number.isAdjacent(symbolList))
		{
			sumParts += number.value;
		}
	}
	std::cout << "Sum of parts numbers: " << sumParts << std::endl;

	int sumRatios = 0;

	for (Symbol symbol : symbolList)
	{
		if (symbol.isAdjacent(numberList))
		{
			std::cout << "test";
			sumRatios += symbol.gearRatio;
			symbol.print();
		}
	}

	std::cout << "Sum of gear ratios: " << sumRatios << std::endl;
	file.close();

	return 0;
}