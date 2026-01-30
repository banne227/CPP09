//############################################################
//#                                                          #
//#   ██████╗ ██████╗ ███╗   ██╗                             #
//#   ██╔══██╗╚════██╗████╗  ██║                             #
//#   ██████╔╝ █████╔╝██╔██╗ ██║                             #
//#   ██╔══██╗██╔═══╝ ██║╚██╗██║                             #
//#   ██████╔╝███████╗██║ ╚████║                             #
//#   ╚═════╝ ╚══════╝╚═╝  ╚═══╝                             #
//#                                                          #
//#   File    : PmergeMe.cpp                                 #
//#   Created : 2026-01-30 16:45                             #
//#   Updated : 2026-01-30 16:45                             #
//#                                                          #
//############################################################

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : time_deq(0), time_vec(0) {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	vec = other.vec;
	deq = other.deq;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		vec = other.vec;
		deq = other.deq;	
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int argc, char** argv)
{
	if (argc < 1)
		throw ERROR();
	
	for (int i = 0; argv[i]; i++)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			if (argv[i][0] == '-' || (argv[i][0] == '0' && argv[i][1] == 0))
				throw NeedPositiveValue();
			if (!isdigit(argv[i][j]) && argv[i][j] != '+')
				throw NeedNumeric();
		}
	}
	for (int i = 0; argv[i]; i++)
	{
		int num = std::atoi(argv[i]);
		vec.push_back(num);
		deq.push_back(num);
	}
}

void PmergeMe::printContainers()
{
	std::cout << "After: ";
	for (int i = 0; vec[i]; i++)
		std::cout << vec[i];
	std::cout << std::endl;

	int size =	vec.size();
	std::cout << "Time to process a range of " << size 
		<< " elements with std::vector : " << this->time_vec << std::endl;
	std::cout << "Time to process a range of " << size 
		<< " elements with std::deque : " << this->time_deq << std::endl;
}

void PmergeMe::sortVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;

	std::vector<int> big;
	std::vector<int> little;
	for (int i = 1; i < vec.size(); i++)
	{
		if (vec[i] > vec[i - 1])
		{
			big.push_back(vec[i]);
			little.push_back(vec[i - 1]);
		}
		else
		{
			big.push_back(vec[i - 1]);
			little.push_back(vec[i]);
		}
		i++;
	}
	if (vec.size() % 2 != 0)
		little.push_back(vec[vec.size() - 1]);
	big = sortVector(big);
}

void PmergeMe::sortDeque()
{
	
}