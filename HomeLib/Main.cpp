#include <iostream>
#include <algorithm>

#include "Testing/Test.h"
#include "Testing/IntrusiveListTest.h"

int main(int argc, char **argv)
{
	std::vector<std::string> testResults =  IntrusiveListTest().RunEntries();

	std::for_each(testResults.begin(), testResults.end(), [&](const std::string &line)
	{
		std::cout << line << std::endl;
	});

	std::system("pause");
	return 0;
}