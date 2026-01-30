#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <ctime>

class NeedNumeric : public std::exception 
{
	public:
		virtual const char* what() const throw() 
		{
			return "Error: All inputs must be numeric values.\n";
		}
};

class NeedPositiveValue : public std::exception 
{
	public:
		virtual const char* what() const throw() 
		{
			return "Error: All inputs must be positive value.\n";
		}
};

class ERROR : public std::exception 
{
	public:
		virtual const char* what() const throw() 
		{
			return "Error\n";
		}
};

class PmergeMe 
{
	private:
		std::vector<int> vec;
		std::deque<int> deq;
		double time_vec;
		double time_deq;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void parseInput(int argc, char** argv);
		void printContainers();
		void sortVector();
		void sortDeque();
};

#endif