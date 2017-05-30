#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <vector>


class Date {
public:
	int year;
	int month;
	int day;

	Date();

	Date(const Date& date);

	Date(int day, int month, int year);

	std::string const to_string();

	std::string to_string(Date date);

	static bool StrToDate(std::string str, Date& date);

	static int max_day_number(int year, int month);

	bool operator<(Date date);

	Date& operator=(Date date);

	bool operator==(Date date);

	friend std::ostream& operator<<(std::ostream& cout, Date date);

	friend std::istream& operator>>(std::istream& cin, Date date);

	~Date();
};