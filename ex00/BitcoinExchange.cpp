//############################################################
//#                                                          #
//#   ██████╗ ██████╗ ███╗   ██╗                             #
//#   ██╔══██╗╚════██╗████╗  ██║                             #
//#   ██████╔╝ █████╔╝██╔██╗ ██║                             #
//#   ██╔══██╗██╔═══╝ ██║╚██╗██║                             #
//#   ██████╔╝███████╗██║ ╚████║                             #
//#   ╚═════╝ ╚══════╝╚═╝  ╚═══╝                             #
//#                                                          #
//#   File    : BitcoinExchange.cpp                          #
//#   Created : 2026-01-28 11:24                             #
//#   Updated : 2026-01-28 11:24                             #
//#                                                          #
//############################################################

#include "BitcoinExchange.hpp"
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	this->dataBase = other.dataBase;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->dataBase = other.dataBase;
	return *this;
}

void    BitcoinExchange::loadData(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		std::cerr << "Error: could not open file " << filename << std::endl;
	std::string line;
	std::getline(file, line); //skip header
	while (std::getline(file, line))
	{
		std::istringstream flux_line(line);
		std::string date;
		std::getline(flux_line, date, ',');
		std::getline(flux_line, line);
		if (date.empty() || line.empty())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		double price = atof(line.c_str());
		dataBase[date] = price;
	}
}

double	BitcoinExchange::getExchangeRate(const std::string& date)
{
	std::map<std::string, double>::iterator value = dataBase.upper_bound(date); //tester auto
	if (value == dataBase.begin())
		throw BadInput();
	--value;
	return value->second;
}

std::string getDate(const std::string& line)
{
	std::istringstream flux_line(line);
	std::string date;
	std::getline(flux_line, date, '|');
	if (date.empty())
		throw BadInput();
	if (date[4] != '-' || date[7] != '-')
		throw BadInput();
	return date;
}

double getValue(const std::string& line)
{
	std::istringstream flux_line(line);
	std::string value_str;

	if (line.find('|') == std::string::npos)
		throw BadInput();

	std::getline(flux_line, value_str, '|');
	std::getline(flux_line, value_str);

	if (value_str.empty())
		throw BadInput();

	double value = atof(value_str.c_str());
	if (value < 0)
		throw NegativeValue();
	if (value > 1000)
		throw ValueTooLarge();
	return value;
}


void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		std::cerr << "Error: could not open file " << filename << std::endl;
	std::string line;
	std::getline(file, line); //skip header
	while (std::getline(file, line))
	{
		try
		{
			std::string date = getDate(line);
			double numbers = getValue(line);
			double value = getExchangeRate(date);
			std::cout << date << " => " << numbers << " = " << numbers * value << std::endl;
		}
		catch (const BadInput& e)
		{
			std::cerr << e.what() << line << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
