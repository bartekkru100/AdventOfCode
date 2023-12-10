#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Shuffle
{
	int red = 0;
	int green = 0;
	int blue = 0;
};

struct Game
{
	int index = 0;
	std::vector<Shuffle> shuffles;

	int getMaxRed()
	{
		int maxRed = 0;
		for(Shuffle shuffle : shuffles)
		{
			if (shuffle.red > maxRed)
			{
				maxRed = shuffle.red;
			}
		}
		return maxRed;
	}
	int getMaxGreen()
	{
		int maxGreen = 0;
		for (Shuffle shuffle : shuffles)
		{
			if (shuffle.green > maxGreen)
			{
				maxGreen = shuffle.green;
			}
		}
		return maxGreen;
	}
	int getMaxBlue()
	{
		int maxBlue = 0;
		for (Shuffle shuffle : shuffles)
		{
			if (shuffle.blue > maxBlue)
			{
				maxBlue = shuffle.blue;
			}
		}
		return maxBlue;
	}
	void printGame()
	{
		std::cout << "Game " << index << ":\n";
		for (Shuffle shuffle : shuffles)
		{
			std::cout << "red:\t" << shuffle.red << "\t";
			std::cout << "green:\t" << shuffle.green << "\t";
			std::cout << "blue:\t" << shuffle.blue << "\n";
		}
	}
};

int main(int argc, char* argv[])
{
	std::fstream file("input.txt");
	if (!file.is_open())
	{
		std::cout << "Can't open file" << std::endl;
		return 1;
	}

	int sumIndexes = 0;
	int sumPowers = 0;

	std::vector<Game> games;
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		line.push_back(';');
		int pos = line.find(':');
		games.push_back(Game());
		games.back().index = stoi(line.substr(5, pos - 5));

		int shuffleCount = 0;
		int endPos = line.find(';', pos);
		pos += 1;
		while (endPos != -1)
		{
			games.back().shuffles.push_back(Shuffle());
			std::string tempStr = line.substr(pos, endPos - pos);
			int redPos = tempStr.find("red");
			if (redPos != -1)
			{
				for (redPos -= 2; isdigit(tempStr[redPos]); redPos--)
				{
					games.back().shuffles.back().red = atoi(&tempStr[redPos]);
				}
			}
			int greenPos = tempStr.find("green");
			if (greenPos != -1)
			{
				for (greenPos -= 2; isdigit(tempStr[greenPos]); greenPos--)
				{
					games.back().shuffles.back().green = atoi(&tempStr[greenPos]);
				}
			}
			int bluePos = tempStr.find("blue");
			if (bluePos != -1)
			{
				for (bluePos -= 2; isdigit(tempStr[bluePos]); bluePos--)
				{
					games.back().shuffles.back().blue = atoi(&tempStr[bluePos]);
				}
			}
			pos = endPos + 1;
			endPos = line.find(';', pos);
		}
		games.back().printGame();
		if (games.back().getMaxRed() <= 12)
		{
			if (games.back().getMaxGreen() <= 13)
			{
				if (games.back().getMaxBlue() <= 14)
				{
					sumIndexes += games.back().index;
					std::cout << "possible\n";
				}
			}
		}
		sumPowers += games.back().getMaxRed() * games.back().getMaxGreen() * games.back().getMaxBlue();
	}
	std::cout << "sum of indexes: " << sumIndexes << std::endl;
	std::cout << "sum of powers: " << sumPowers << std::endl;
	return 0;
}