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
#include <iomanip>
#include <time.h>

PmergeMe::PmergeMe() {}

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
	std::cout << "After : ";
	for (int i = 0; vec[i]; i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;

	int size =	vec.size();
	std::cout << "Time to process a range of " << size 
		<< " elements with std::vector : " << std::fixed << std::setprecision(5) << this->time_vec << " us" << std::endl;
	std::cout << "Time to process a range of " << size 
		<< " elements with std::deque : " << std::fixed << std::setprecision(5) << this->time_deq << " us" << std::endl;
}

void PmergeMe::sortVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;

	std::vector<int> big;
	std::vector<int> little;
	for (long unsigned int i = 1; i < vec.size(); i += 2)
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
	}
	if (vec.size() % 2 != 0)
		little.push_back(vec[vec.size() - 1]);
	sortVector(big);
	for (long unsigned int i = 0; i < little.size(); i++)
	{
		std::vector<int>::iterator it = std::lower_bound(big.begin(), big.end(), little[i]);
		big.insert(it, little[i]);
	}
	vec = big;
}

void PmergeMe::sortDeque(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return;

	std::deque<int> big;
	std::deque<int> little;
	for (long unsigned int i = 1; i < deq.size(); i += 2)
	{
		if (deq[i] > deq[i - 1])
		{
			big.push_back(deq[i]);
			little.push_back(deq[i - 1]);
		}
		else
		{
			big.push_back(deq[i - 1]);
			little.push_back(deq[i]);
		}
	}
	if (deq.size() % 2 != 0)
		little.push_back(deq[deq.size() - 1]);
	sortDeque(big);
	for (long unsigned int i = 0; i < little.size(); i++)
	{
		std::deque<int>::iterator it = std::lower_bound(big.begin(), big.end(), little[i]);
		big.insert(it, little[i]);
	}
	deq = big;
}

void PmergeMe::sortContainers()
{
	struct timespec start_vec, end_vec;
	clock_gettime(CLOCK_MONOTONIC, &start_vec);
	sortVector(this->vec);
	clock_gettime(CLOCK_MONOTONIC, &end_vec);
	this->time_vec = (end_vec.tv_sec - start_vec.tv_sec) * 1000000.0 + (end_vec.tv_nsec - start_vec.tv_nsec) / 1000.0;

	struct timespec start_deq, end_deq;
	clock_gettime(CLOCK_MONOTONIC, &start_deq);
	sortDeque(this->deq);
	clock_gettime(CLOCK_MONOTONIC, &end_deq);
	this->time_deq = (end_deq.tv_sec - start_deq.tv_sec) * 1000000.0 + (end_deq.tv_nsec - start_deq.tv_nsec) / 1000.0;
}