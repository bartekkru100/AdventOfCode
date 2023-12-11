#include "Number.h"

Number::Number(int row, int pos, int value)
{
	this->row = row;
	this->pos = pos;
	this->value = value;
}

 int Number::length()
{
	return std::to_string(value).length();
}

void Number::print()
{
	std::cout << "number:\t" << value << "\trow:\t" << row << "\tpos:\t" << pos << "\tis part?:\t" << isPart << '\n';
}

bool Number::isAdjacent(std::list<Symbol>& symbolList)
{
	for (Symbol symbol : symbolList)
	{
		if ((row - 2) < symbol.row && symbol.row < (row + 2))
		{
			if ((pos - 2) < symbol.pos && symbol.pos < (pos + length() + 1))
			{
				isPart = true;
				return true;
			}
		}
	}
	return false;
}
