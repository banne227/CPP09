//############################################################
//#                                                          #
//#   ██████╗ ██████╗ ███╗   ██╗                             #
//#   ██╔══██╗╚════██╗████╗  ██║                             #
//#   ██████╔╝ █████╔╝██╔██╗ ██║                             #
//#   ██╔══██╗██╔═══╝ ██║╚██╗██║                             #
//#   ██████╔╝███████╗██║ ╚████║                             #
//#   ╚═════╝ ╚══════╝╚═╝  ╚═══╝                             #
//#                                                          #
//#   File    : BitcoinExchange.hpp                          #
//#   Created : 2026-01-28 11:16                             #
//#   Updated : 2026-01-28 11:16                             #
//#                                                          #
//############################################################

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

class NegativeValue : public std::exception 
{
public:
	virtual const char* what() const throw() 
	{
		return "Error: not a positive number.";
	}
};


class BadInput : public std::exception 
{
	public:
		virtual const char* what() const throw() 
		{
			return "Error: bad input => ";
		}
};

class ValueTooLarge : public std::exception 
{
	public:
		virtual const char* what() const throw() 
		{
			return "Error: too large a number.";
		}
};

class BitcoinExchange 
{
	private:
		std::map<std::string, double> dataBase;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

		void    loadData(const std::string& filename);
		double	getExchangeRate(const std::string& date);
		void processInput(const std::string& filename);

};

#endif