#pragma once

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>
#include <ctime>
#include <cctype>

std::vector<std::string> Split(const std::string &str, char separator)
{
	std::vector<std::string> parts;
	std::size_t start = 0, end = 0;
	while ((end = str.find(separator, start)) != std::string::npos) {
		if (end != start) {
			parts.push_back(str.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		parts.push_back(str.substr(start));
	}
	return parts;
}