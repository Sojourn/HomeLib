#include "IntrusiveListTest.h"
#include "../Containers/IntrusiveList.h"

#include <array>

// By default constructs a 'unique' item which can be added to an intrusive list.
// We get a comparison for free with (*this).data == other.data
struct ListItem
{
	ListItem() : data(rand()) {}

	int data;
	IntrusiveLink link;
};

// Create a type alias for a list of items
typedef IntrusiveList<ListItem, offsetof(ListItem, link)> IntrusiveItemList;

Test IntrusiveListTest()
{
	Test test("IntrusiveList");

	TestEntry push_backTest;
	push_backTest.name = "push_back test";
	push_backTest.test = []() -> bool
	{
		IntrusiveItemList list;
		std::array<ListItem, 1024> items;
		std::for_each(items.begin(), items.end(), [&list](ListItem &item)
		{
			list.push_back(item);
		});

		// Check if we added all of the items
		if(list.size() != items.size()) return false;

		// Check the ordering of the items in the list
		size_t index = 0;
		for(auto i = list.begin(); i != list.end(); i++)
		{
			if((items[index]).data != (*i).data) return false; 
			index++;
		}

		return true;
	};
	test.AddEntry(push_backTest);

	TestEntry push_frontTest;
	push_frontTest.name = "push_front test";
	push_frontTest.test = []() -> bool
	{
		IntrusiveItemList list;
		std::array<ListItem, 1024> items;
		std::for_each(items.begin(), items.end(), [&list](ListItem &item)
		{
			list.push_front(item);
		});

		// Check if we added all of the items
		if(list.size() != items.size()) return false;

		// Check the ordering of the items in the list
		size_t index = 1024 - 1;
		for(auto i = list.begin(); i != list.end(); i++)
		{
			if((items[index]).data != (*i).data) return false; 
			index--;
		}

		return true;
	};
	test.AddEntry(push_frontTest);

	TestEntry eraseTest;
	eraseTest.name = "erase test";
	eraseTest.test = []() -> bool
	{
		IntrusiveItemList list;
		ListItem a;
		ListItem b;
		ListItem c;

		list.push_back(a);
		list.push_back(b);
		list.push_back(c);

		// Erase the front item
		list.erase(a);
		if(&list.front() != &b) return false;
		if(&list.back() != &c) return false;
		list.push_front(a);

		// Erase the back item
		list.erase(c);
		if(&list.front() != &a) return false;
		if(&list.back() != &b) return false;
		list.push_back(c);

		// Erase a middle item
		list.erase(b);
		if(&list.front() != &a) return false;
		if(&list.back() != &c) return false;

		return true;
	};
	test.AddEntry(eraseTest);

	TestEntry insertTest;
	insertTest.name = "insert test";
	insertTest.test = []() -> bool
	{
		IntrusiveItemList list;
		ListItem a;
		ListItem b;
		ListItem c;

		list.push_back(a);
		list.push_back(b);
		list.push_back(c);

		// Insert at front
		list.erase(a);
		list.insert(list.cbegin(), a);
		if(&list.front() != &a) return false;
		if(&(*(++list.cbegin())) != &b) return false;
		if(&list.back() != &c) return false;

		// Insert at back
		list.erase(c);
		list.insert(list.cend(), c);
		if(&list.front() != &a) return false;
		if(&(*(++list.cbegin())) != &b) return false;
		if(&list.back() != &c) return false;

		// Insert at middle
		list.erase(b);
		list.insert(++list.cbegin(), b);
		if(&list.front() != &a) return false;
		if(&(*(++list.cbegin())) != &b) return false;
		if(&list.back() != &c) return false;

		return true;
	};
	test.AddEntry(insertTest);

	return test;
}