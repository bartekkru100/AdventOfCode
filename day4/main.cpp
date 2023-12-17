#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

struct Card
{
	int number = 0;
	std::vector<int> winNums;
	std::vector<int> myNums;
	int count = 0;
	int value = 0;
	Card(std::string &input)
	{
		number = atoi(&input[input.find_first_not_of(' ', 4)]);
		int pos = input.find(':') + 2;
		int winningCutoff = input.find('|');
		int length = input.length();
		while (pos < winningCutoff - 1)
		{
			if (isdigit(input[pos]))
			{
				winNums.push_back(atoi(&input[pos]));
				if (winNums.back() > 9)
				{
					pos += 2;
					continue;
				}
			}
			pos++;
		}
		pos = winningCutoff + 2;
		while (pos < length)
		{
			if (isdigit(input[pos]))
			{
				myNums.push_back(atoi(&input[pos]));
				if (myNums.back() > 9)
				{
					pos += 2;
					continue;
				}
			}
			pos++;
		}
		getValue();
		getCount();
	}
	int getValue()
	{
		int value = 0;
		for (int winNum : winNums)
		{
			for (int myNum : myNums)
			{
				if (winNum == myNum)
				{
					if (value == 0)
					{
						value = 1;
					}
					else
					{
						value *= 2;
					}
					break;
				}
			}
		}
		this->value = value;
		return value;
	}
	int getCount()
	{
		int count = 0;
		for (int winNum : winNums)
		{
			for (int myNum : myNums)
			{
				if (winNum == myNum)
				{
					count++;
					break;
				}
			}
		}
		this->count = count;
		return count;
	}
	void printCard()
	{
		std::cout << "card " << number << "\nwinning numbers:\n";
		for (int num : winNums)
		{
			std::cout << num << '\t';
		}
		std::cout << "\nyour numbers:\n";
		for (int num : myNums)
		{
			std::cout << num << '\t';
		}
		std::cout << "\ncard value: " << getValue() << "\n--------------------------------\n";
	}
	//friend countCards();
};

int countCards(Card& card, std::vector<Card>& cards, int &cardsSize)
{
	int count = card.count;
	int initCount = count;
	int cardNum = card.number;
	for (int i = 0; ((i < initCount) && (cardNum + i < cardsSize)); i++)
	{
		count += countCards(cards[cardNum + i], cards, cardsSize);
	}
	return count;
}

int main(int argc, char* argv[])
{
	auto begin = std::chrono::high_resolution_clock::now();
	std::fstream file("input.txt");
	if (!file.is_open())
	{
		return 1;
	}

	std::vector<Card> cards;
	std::string line;

	int sumValue = 0;

	for (int i = 1; getline(file, line); i++)
	{
		//std::cout << "card " << i << ": " << '\n';
		cards.push_back(line);
		//cards.back().printCard();
		sumValue += cards.back().value;
		//std::cout << cards.back().getCount() << '\n';
	}
	int sumCards = 0;
	int cardsSize = cards.size();
	for (Card card : cards)
	{
		//std::cout << "card " << card.number << ": " << '\n';
		sumCards += countCards(card, cards, cardsSize) + 1;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = end - begin;
	std::cout << "Sum of values: " << sumValue << std::endl;
	std::cout << "Sum of cards: " << sumCards << std::endl;
	std::cout << "exec time: " << elapsed.count()/1e6 << "ms\n";
	file.close();
	return 0;
}