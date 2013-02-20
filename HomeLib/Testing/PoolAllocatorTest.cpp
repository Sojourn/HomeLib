#include "PoolAllocatorTest.h"
#include "../Memory/PoolAllocator.h"

std::vector<std::string> Testing::TestPoolAllocator()
{
	Test test("PoolAllocator");

	TestEntry AllocateTest;
	AllocateTest.name = "Allocate test";
	AllocateTest.test = []() -> bool
	{
		Memory::PoolAllocator allocator(128);
		return true;
	};
	test.AddEntry(AllocateTest);

	return test.RunEntries();
}