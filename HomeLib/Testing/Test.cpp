#include "Test.h"
#include <algorithm>
#include <sstream>

Testing::Test::Test(const std::string &name) :
	_name(name)
{
}

void Testing::Test::AddEntry(TestEntry &entry)
{
	_tests.push_back(entry);
}

std::vector<std::string> Testing::Test::RunEntries()
{
	std::vector<std::string> result;
	result.push_back("Testing  [" + _name + "]");

	std::for_each(_tests.begin(), _tests.end(), [&result](TestEntry &entry)
	{
		std::stringstream ss;
		ss << entry.name << ": ";
		ss << (entry.test() ? "Passed" : "Failed");
		result.push_back(ss.str());
	});

	result.push_back("Complete [" + _name + "]");
	return result;
}