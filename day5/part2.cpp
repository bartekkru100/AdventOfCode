#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <cmath>

typedef long long int_L;
typedef std::vector<int_L> IntVec;

struct SeedRange
{
	int_L srcFirst;
	int_L srcLast;
	int_L dstFirst;
	int_L dstLast;
	int_L dstNewFirst;
	int_L dstNewLast;
	int_L length()
	{
		return srcLast - srcFirst;
	}
	void update()
	{
		dstFirst = dstNewFirst;
		dstLast = dstNewLast;
	}
	SeedRange trimFirst(int_L value)
	{
		SeedRange seedRange;
		seedRange.srcFirst = srcFirst;
		seedRange.dstFirst = dstFirst;
		seedRange.dstNewFirst = dstFirst;
		srcFirst -= value;
		dstFirst -= value;
		//dstNewFirst -= value;
		seedRange.srcLast = srcFirst - 1;
		seedRange.dstLast = dstFirst - 1;
		seedRange.dstNewLast = dstFirst - 1;
		std::cout << srcFirst << '\t' << '\t' << '\t' << srcLast << '\n';
		std::cout << dstFirst << '\t' << '\t' << '\t' << dstLast << '\n';
		std::cout << dstNewFirst << '\t' << '\t' << '\t' << dstNewLast << '\n';
		return seedRange;
	}
	SeedRange trimLast(int_L value)
	{
		SeedRange seedRange;
		seedRange.srcLast = srcLast;
		seedRange.dstLast = dstLast;
		seedRange.dstNewLast = dstLast;
		srcLast += value;
		dstLast += value;
		//dstNewLast += value;
		seedRange.srcFirst = srcLast + 1;
		seedRange.dstFirst = dstLast + 1;
		seedRange.dstNewFirst = dstLast + 1;
		std::cout << srcFirst << '\t' << '\t' << '\t' << srcLast << '\n';
		std::cout << dstFirst << '\t' << '\t' << '\t' << dstLast << '\n';
		std::cout << dstNewFirst << '\t' << '\t' << '\t' << dstNewLast << '\n';
		return seedRange;
	}
};

int nIntDigits(int_L num)
{
	int nDigits = 1;
	for (int_L multiplier = 10; num >= multiplier; multiplier *= 10, nDigits++);
	return nDigits;
}

int main()
{
	auto begin = std::chrono::high_resolution_clock::now();
	std::fstream file("input.txt");
	if (!file.is_open())
	{
		return 1;
	}

	std::vector<SeedRange> seeds;
	std::string line;
	std::getline(file, line);
	size_t pos = line.find(':') + 2;
	for (; pos < line.size(); pos++)
	{
		if (isdigit(line[pos]))
		{
			seeds.push_back(SeedRange());
			seeds.back().srcFirst = atoll(&line[pos]);
			pos += nIntDigits(seeds.back().srcFirst);
			seeds.back().srcLast = seeds.back().srcFirst + atoll(&line[pos]);
			pos += nIntDigits(seeds.back().srcLast);
			seeds.back().dstFirst = seeds.back().srcFirst;
			seeds.back().dstLast = seeds.back().srcLast;
			seeds.back().dstNewFirst = seeds.back().srcFirst;
			seeds.back().dstNewLast = seeds.back().srcLast;
			std::cout << "first:\t" << seeds.back().srcFirst << '\t' << seeds.back().dstFirst << '\n';
			std::cout << "last:\t" << seeds.back().srcLast << '\t' << seeds.back().dstLast << '\n';
			std::cout << "-----------------------------------------\n";
		}
	}
	std::cout << "\n-----------------------------------------\n";

	IntVec destinStart;
	IntVec sourceStart;
	IntVec rangeLength;

	std::getline(file, line);
	int i = 0;
	while (!file.eof())
	//while (i == 0)
	{
		i++;
		destinStart.clear();
		sourceStart.clear();
		rangeLength.clear();

		std::getline(file, line);
		std::cout << line << '\n';
		while (std::getline(file, line))
		{
			if (!isdigit(line[0]))break;
			pos = 0;
			destinStart.push_back(atoll(&line[pos]));
			pos += nIntDigits(destinStart.back()) + 1;
			sourceStart.push_back(atoll(&line[pos]));
			pos += nIntDigits(sourceStart.back()) + 1;
			rangeLength.push_back(atoll(&line[pos]));
		}

		int i = 0;
		for (SeedRange &seedRange : seeds)
		{
			std::cout << &seedRange << '\n';
			std::cout << &seeds[3] << '\n';
			std::cout << '\n';
			if (seedRange.srcFirst != seeds[3].srcFirst) continue;
			i++;
			bool isMapped = false;
			for (int i = 0; i < destinStart.size(); i++)
			{
				int_L firstSeedDistance = seedRange.dstFirst - sourceStart[i];
				int_L lastSeedDistance = (sourceStart[i] + rangeLength[i] - 1) - seedRange.dstLast;
				bool isFirstBefore = firstSeedDistance < 0;
				bool isLastAfter = lastSeedDistance < 0;
				bool isFirstInRange = firstSeedDistance <= rangeLength[i] - 1 && !isFirstBefore;
				bool isLastInRange = lastSeedDistance <= rangeLength[i] - 1 && !isLastAfter;

				std::cout << seedRange.srcFirst << '\t' << '\t' << '\t' << seedRange.srcLast << '\n';
				std::cout << seedRange.dstFirst << '\t' << sourceStart[i] << '\t' << seedRange.dstLast << '\t' << sourceStart[i] + rangeLength[i] - 1 << '\n';
				std::cout << seedRange.dstNewFirst << '\t' << destinStart[i] << '\t' << seedRange.dstNewLast << '\t' << destinStart[i] + rangeLength[i] - 1 << '\n';
				std::cout << firstSeedDistance << '\t' << '\t' << '\t' << lastSeedDistance << '\n';

				if ((isFirstInRange || isFirstBefore) && isLastAfter)
				{
					std::cout << "Extends after" << '\n';

					seeds.push_back(seedRange.trimLast(lastSeedDistance));

					seedRange.dstNewLast = destinStart[i] + rangeLength[i] - 1;

				}
				if ((isLastInRange || isLastAfter) && isFirstBefore)
				{
					std::cout << "Extends before" << '\n';

					seeds.push_back(seedRange.trimFirst(firstSeedDistance));

					seedRange.dstNewFirst = destinStart[i];
					std::cout << seedRange.srcFirst << '\t' << '\t' << '\t' << seedRange.srcLast << '\n';
					std::cout << seedRange.dstFirst << '\t' << '\t' << '\t' << seedRange.dstLast << '\n';
					std::cout << seedRange.dstNewFirst << '\t' << '\t' << '\t' << seedRange.dstNewLast << '\n';
				}
				if (isFirstInRange)
				{
					std::cout << "First in range" << '\n';
					seedRange.dstNewFirst = destinStart[i] + firstSeedDistance;
				}
				if (isLastInRange)
				{
					std::cout << "Last in range" << '\n';
					seedRange.dstNewLast = destinStart[i] + firstSeedDistance + seedRange.length() - 1;
				}
				std::cout << '\n';
			}

			std::cout << "src:\t" << seedRange.srcFirst << '\t' << seedRange.srcLast << '\n';
			std::cout << "dst:\t" << seedRange.dstFirst << '\t' << seedRange.dstLast << '\n';
			seedRange.update();
			std::cout << "newdst:\t" << seedRange.dstFirst << '\t' << seedRange.dstLast << '\n';
			std::cout << "-----------------------------------------\n";
			//std::cout << seed << '\t' << seedToDestin[seed] << '\n';
		}
	}
	int_L lowestLocationNum = INT64_MAX;
	for (auto seedRange : seeds)
	{
		//std::cout << seed << '\t' << seedToDestin[seed] << '\n';
		if (seedRange.dstFirst < lowestLocationNum)
		{
			lowestLocationNum = seedRange.dstFirst;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = end - begin;
	std::cout << "lowest location number: " << lowestLocationNum << '\n';
	std::cout << "exec time: " << elapsed.count() / 1e6 << "ms\n" << seeds.size();

	file.close();
	return 0;
}