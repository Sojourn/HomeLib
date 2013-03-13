#include <iostream>
#include <algorithm>

#include "Testing/Test.h"
#include "Testing/IntrusiveListTest.h"
#include "Testing/PoolAllocatorTest.h"
#include "Containers/DynamicArray.h"
#include "Containers/Array2D.h"

int main(int argc, char **argv)
{
	auto report = [](std::vector<std::string> &results)
	{
		std::for_each(results.begin(), results.end(), [&](const std::string &line)
		{
			std::cout << line << std::endl;
		});
	};

	// report(Testing::TestIntrusiveList());
	// report(Testing::TestPoolAllocator());

	Container::Array2D<char> doc(64, 1024);
	for(size_t y = 0; y < doc.height(); y++)
		for(size_t x = 0; x < doc.width(); x++)
			doc[y][x] = (y * x) % 127;
	doc.at(3, 4) = 6;
	doc.at(0, 0) = 7;
	doc.at(63, 1023) = 9;

	Container::Array2D<char> doc2(doc);
	Container::Array2D<char> doc3(64, 64);
	doc3 = doc2;

	for(size_t y = 0; y < doc.height(); y++)
	for(size_t x = 0; x < doc.width(); x++)
		doc[y][x] = (y * x) % 127;
	doc3.at(3, 4) = 6;
	doc3.at(0, 0) = 7;
	doc3.at(63, 1023) = 9;

	std::system("pause");
	return 0; 
}