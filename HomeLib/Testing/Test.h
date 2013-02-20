#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include <functional>
#include <cstdint>
#include <tuple>

namespace Testing
{

	struct TestEntry
	{
		std::string name;
		std::function<bool (void)> test;
	};

	class Test
	{
	public:
		Test(const std::string &name);

		// Add a test entry
		void AddEntry(TestEntry &entry);

		// Run entries and return the results in a vector
		std::vector<std::string> RunEntries();

	private:
		const std::string _name;
		std::vector<TestEntry> _tests;
	};

}

#endif // TEST_H