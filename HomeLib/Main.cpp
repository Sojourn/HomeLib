#include <iostream>
#include <algorithm>

#include "Testing/Test.h"
#include "Testing/IntrusiveListTest.h"
#include "Testing/PoolAllocatorTest.h"

int main(int argc, char **argv)
{
	auto report = [](std::vector<std::string> &results)
	{
		std::for_each(results.begin(), results.end(), [&](const std::string &line)
		{
			std::cout << line << std::endl;
		});
	};

	report(Testing::TestIntrusiveList());
	report(Testing::TestPoolAllocator());

	std::system("pause");
	return 0;
}