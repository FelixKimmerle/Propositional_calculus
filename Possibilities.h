#pragma once
#include <iostream>
#include <vector>

namespace Possibilities
{
	std::vector<std::string> calc(const std::string &table, size_t length);
	std::vector<std::string> calcboolean(size_t length);
}
