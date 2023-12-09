#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

int main(int argc, char* argv[])
{
	std::fstream file("input.txt");
	if (!file.is_open())
	{
		std::cout << "Failed to open file";
		return 1;
	}

	std::string line;
	char leftmost;
	char rightmost;
	std::list<int> numbers;
	int sum = 0;

	std::map<std::string, char> lookupTable;
	lookupTable["one"]		= '1';
	lookupTable["two"]		= '2';
	lookupTable["three"]	= '3';
	lookupTable["four"]		= '4';
	lookupTable["five"]		= '5';
	lookupTable["six"]		= '6';
	lookupTable["seven"]	= '7';
	lookupTable["eight"]	= '8';
	lookupTable["nine"]		= '9';

	while (file >> line)
	{
		std::cout << "line:\t" << line << "\n";
		leftmost = -1;
		rightmost = -1;
		int lowest = line.length();
		int highest = -1;
		for (auto num : lookupTable)
		{
			int index = line.find(num.first);
			if (index == -1);
			else if (index < lowest)
			{
				lowest = index;
				leftmost = num.second;
			}
			index = line.find(num.second);
			if (index == -1);
			else if (index < lowest)
			{
				lowest = index;
				leftmost = num.second;
			}

			index = line.rfind(num.first);
			if (index > highest)
			{
				highest = index;
				rightmost = num.second;
			}
			index = line.rfind(num.second);
			if (index > highest)
			{
				highest = index;
				rightmost = num.second;
			}
		}
		char num[2] = { leftmost, rightmost };
		numbers.push_back(atoi(num));
		std::cout << "number:\t" << numbers.back() << "\n";
		sum += numbers.back();
		std::cout << "sum:\t" << sum << std::endl;
	}
	
	file.close();
	return 0;
}