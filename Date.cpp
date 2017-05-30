#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>
#include <ctime>
#include "Split.h"
#include "Date.h"


bool CheckDate(std::string date) {
	std::vector<std::string> tempvect = Split(date, '.');
	if (tempvect.size() != 3) return false;
	try {
		int year = std::stoi(tempvect[2]);
		if (year < 1900 || year > 2017) return false;

		int month = std::stoi(tempvect[1]);
		if (month < 1 || month > 12) return false;

		int day = std::stoi(tempvect[0]);
		if (day < 1 || day > Date::max_day_number(year, month)) return false;
	}
	catch (...) {
		return false;
	}
	return true;
}

Date::Date()
{
	year = 1900;
	month = 1;
	day = 1;
}

Date::Date(const Date & date)
{
	year = date.year;
	month = date.month;
	day = date.day;
}

Date::Date(int day, int month, int year)
{

	this->year = year;
	if ((month < 1) || (month > 12)) {
		throw std::out_of_range("Incorrect month (1..12)!");
	}
	this->month = month;


	int max_day = max_day_number(year, month);

	if ((day < 1) || (day > max_day)) {
		throw std::out_of_range("Incorrect day (1.." + std::to_string(max_day) + ")!");
	}
	this->day = day;
}

std::string const Date::to_string()
{
	return std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
}

std::string Date::to_string(Date date)
{
	return std::to_string(date.day) + '.' + std::to_string(date.month) + '.' + std::to_string(date.year);
}

bool Date::StrToDate(std::string str, Date & date)
{
	if (!CheckDate(str))
		return false;

	std::vector<std::string> tempvect = Split(str, '.');

	try {
		date.day = std::stoi(tempvect[0]);
	}
	catch (std::exception e) {
		return false;
	}

	try {
		date.month = std::stoi(tempvect[1]);
	}
	catch (std::exception e) {
		return false;
	}

	try {
		date.year = std::stoi(tempvect[2]);
	}
	catch (std::exception e) {
		return false;
	}

	return true;
}

int Date::max_day_number(int year, int month)
{

	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)) {
		return 31;
	}
	else if (month == 2) {
		if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0)) {
			return 29;
		}
		else {
			return 28;
		}
	}
	else {
		return 30;
	}
}

bool Date::operator<(Date date)
{
	if (year != date.year) {
		return year < date.year;
	}

	if (month != date.month) {
		return month < date.month;
	}

	if (day != date.day) {
		return day < date.day;
	}

	return false;
}

Date & Date::operator=(Date date)
{
	year = date.year;
	month = date.month;
	day = date.day;
	return *this;
}

bool Date::operator==(Date date)
{
	return (year == date.year) && (month == date.month) && (day == date.day);
}

Date::~Date()
{

}

std::ostream & operator<<(std::ostream & cout, Date date)
{
	cout << date.to_string();
	return cout;
}

std::istream & operator >> (std::istream & cin, Date date)
{
	std::string buf;
	bool ok = false;
	cin >> buf;
	ok = date.StrToDate(buf, date);
	if (!ok)
		std::cout << "Неверная дата!";

	return cin;
}