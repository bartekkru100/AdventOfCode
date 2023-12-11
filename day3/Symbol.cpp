#include "Symbol.h"

Symbol::Symbol(int row, int pos, char value)
{
	this->row = row;
	this->pos = pos;
	this->value = value;
}

void Symbol::print()
{
	std::cout << "symbol:\t" << value << "\trow:\t" << row << "\tpos:\t" << pos << "\tgear ratio:\t" << gearRatio << '\n';
}
bool Symbol::isAdjacent(std::list<Number>& numberList)
{
	isGear = false;
	adjacentParts.clear();
	gearRatio = 1;
	for (Number number : numberList)
	{
		if ((number.row - 2) < row && row < (number.row + 2))
		{
			if ((number.pos - 2) < pos && pos < (number.pos + number.length() + 1))
			{
				adjacentParts.push_back(& number);
				gearRatio *= adjacentParts.back()->value;
			}
		}
	}
	if (adjacentParts.size() == 2 && value == '*')
	{
		isGear = true;
		return true;
	}
	return false;
}