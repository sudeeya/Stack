#include "Stack.h"
#include <iostream>

bool getInitialCapacityTest();
bool getMemoryMultiplierTest();
bool equalityOperatorTest();
bool inequalityOperatorTest();
bool sizeTest();
bool capacityTest();
bool isEmptyTest();
bool peekTest();
bool popTest();
bool pushTest();
bool tests();

int main() {
	tests();
	return 0;
}

bool getInitialCapacityTest() {
	Stack tmp;
	if (tmp.getInitialCapacity() != 32) {
		std::cout << "Initial capacity test failed." << std::endl;
		return false;
	}
	return true;
}

bool getMemoryMultiplierTest() {
	Stack tmp;
	if (tmp.getMemoryMultiplier() != 2) {
		std::cout << "Memory multiplier test failed." << std::endl;
		return false;
	}
	return true;
}

bool equalityOperatorTest() {
	double data[] = { 5.0, 6.98 , 8.4, 9, 7.54, 3.45 };
	Stack lhs{ data, 6 }, rhs{ lhs };
	if (lhs == rhs)
		return true;
	std::cout << "Equality test failed." << std::endl;
	return false;
}

bool inequalityOperatorTest() {
	double data[] = { 5.0, 6.98 , 8.4, 9, 7.54, 3.45 };
	Stack lhs{ data, 6 }, rhs{ data, 4 };
	if (lhs != rhs)
		return true;
	std::cout << "Inequality test failed." << std::endl;
	return false;
}

bool sizeTest() {
	double data[] = { 1.2, 3.5, 7.54, -6.4, -95.2 };
	Stack first{}, second{ data, 5 };
	if (first.size() == 0 && second.size() == 5)
		return true;
	std::cout << "Size test failed." << std::endl;
	return false;
}

bool capacityTest() {
	double data[70] = { 0 };
	Stack first{}, second{ data, 70 };
	if (first.capacity() == 32 && second.capacity() == 128)
		return true;
	std::cout << "Capacity test failed." << std::endl;
	return false;
}

bool isEmptyTest() {
	double data[] = { 1.2, 3.65, -8.64 };
	Stack first{}, second{ data, 3 };
	if (first.isEmpty() == true && second.isEmpty() == false)
		return true;
	std::cout << "Emptiness test failed." << std::endl;
	return false;
}

bool peekTest() {
	double data[] = { 1.2, 3.65, -8.64 };
	Stack first{ data, 1 }, second{ data, 3 };
	if (first.peek() == 1.2 && second.peek() == -8.64)
		return true;
	std::cout << "Peek test failed." << std::endl;
	return false;
}

bool popTest() {
	double data[] = { 1.2, 3.65, -8.64, 5.59, -7.5, -0.67 };
	Stack first{ data, 4 }, second{ data, 6 };
	if (first.pop() == 5.59 && second.pop() == -0.67)
		return true;
	std::cout << "Pop test failed." << std::endl;
	return false;
}

bool pushTest() {
	double data[] = { 1.2, 3.65, -8.64, 5.59, -7.5, -0.67, 1.29 };
	Stack first{ data, 4 }, second{ data, 6 }, firstRes{ data, 5 }, secondRes{ data, 7 };
	first.push(-7.5);
	second.push(1.29);
	if (first == firstRes && second == secondRes)
		return true;
	std::cout << "Push test failed." << std::endl;
	return false;
}

bool tests() {
	size_t numberOfFails = 0;
	if (!getInitialCapacityTest())
		++numberOfFails;
	if (!getMemoryMultiplierTest())
		++numberOfFails;
	if (!equalityOperatorTest())
		++numberOfFails;
	if (!inequalityOperatorTest())
		++numberOfFails;
	if (!sizeTest())
		++numberOfFails;
	if (!capacityTest())
		++numberOfFails;
	if (!isEmptyTest())
		++numberOfFails;
	if (!peekTest())
		++numberOfFails;
	if (!popTest())
		++numberOfFails;
	if (!pushTest())
		++numberOfFails;
	if (numberOfFails == 0) {
		std::cout << "Everything is fine." << std::endl;
		return true;
	}
	std::cout << "Number of failed tests: " << numberOfFails << '.' << std::endl;
	return false;
}