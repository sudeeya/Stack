#include <iostream>
#include "stack.h"

bool EqualityOperatorTest();
bool InequalityOperatorTest();
bool SizeTest();
bool CapacityTest();
bool IsEmptyTest();
bool TopTest();
bool PopTest();
bool PushTest();
bool Tests();

int main() {
	Tests();
	return 0;
}

bool EqualityOperatorTest() {
	double data[] = { 5.0, 6.98 , 8.4, 9, 7.54, 3.45 };
	bool b_data[] = { false, true, true, true, false, true };
	stack_project::Stack<double> lhs{ data, 6 }, rhs{ lhs };
	stack_project::Stack<bool> b_lhs{ b_data, 6 }, b_rhs{ b_lhs };
	if (lhs == rhs && b_lhs == b_rhs)
		return true;
	std::cout << "Equality test failed." << std::endl;
	return false;
}

bool InequalityOperatorTest() {
	double data[] = { 5.0, 6.98 , 8.4, 9, 7.54, 3.45 };
	bool b_data[] = { false, true, true, true, false, true };
	stack_project::Stack<double> lhs{ data, 6 }, rhs{ data, 4 };
	stack_project::Stack<bool> b_lhs{ b_data, 6 }, b_rhs{ b_data, 4 };
	if (lhs != rhs && b_lhs != b_rhs)
		return true;
	std::cout << "Inequality test failed." << std::endl;
	return false;
}

bool SizeTest() {
	double data[] = { 1.2, 3.5, 7.54, -6.4, -95.2 };
	bool b_data[] = { false, true, true, true, false, true };
	stack_project::Stack<double> first, second{ data, 5 };
	stack_project::Stack<bool> b_first, b_second{ b_data, 6 };
	if (first.size() == 0 && second.size() == 5 &&
		b_first.size() == 0 && b_second.size() == 6) {
		return true;
	}
	std::cout << "Size test failed." << std::endl;
	return false;
}

bool CapacityTest() {
	double data[70] = { 0 };
	bool b_data[] = { false, true, true, true, false, true };
	stack_project::Stack<double> first, second{ data, 70 };
	stack_project::Stack<bool> b_first, b_second{ b_data, 6 };
	if (first.capacity() == 32 && second.capacity() == 128 &&
		b_first.capacity() == 32 && b_second.capacity() == 32) { 
		return true;
	}
	std::cout << "Capacity test failed." << std::endl;
	return false;
}

bool IsEmptyTest() {
	double data[] = { 1.2, 3.65, -8.64 };
	bool b_data[] = { false, true, true, true, false, true };
	stack_project::Stack<double> first, second{ data, 3 };
	stack_project::Stack<bool> b_first, b_second{ b_data, 6 };
	if (first.is_empty() == true && second.is_empty() == false &&
		b_first.is_empty() == true && b_second.is_empty() == false) { 
		return true;
	}
	std::cout << "Emptiness test failed." << std::endl;
	return false;
}

bool TopTest() {
	double data[] = { 1.2, 3.65, -8.64 };
	bool b_data[] = { false, true, true, true, false, true };
	stack_project::Stack<double> first{ data, 1 }, second{ data, 3 };
	stack_project::Stack<bool> b_first{ b_data, 1 }, b_second{ b_data, 3 };
	if (first.top() == 1.2 && second.top() == -8.64 &&
		!b_first.top() && b_second.top())
		return true;
	std::cout << "Peek test failed." << std::endl;
	return false;
}

bool PopTest() {
	double data[] = { 1.2, 3.65, -8.64, 5.59, -7.5, -0.67 };
	bool b_data[] = { false, true, true, true, false, true };
	stack_project::Stack<double> first{ data, 4 }, second{ data, 6 };
	stack_project::Stack<bool> b_first{ b_data, 5 }, b_second{ b_data, 6 };
	if (first.pop() == 5.59 && second.pop() == -0.67 &&
		!b_first.pop() && b_second.pop()) { 
		return true;
	}
	std::cout << "Pop test failed." << std::endl;
	return false;
}

bool PushTest() {
	double data[] = { 1.2, 3.65, -8.64, 5.59, -7.5, -0.67, 1.29 };
	bool b_data[] = { false, true, true, true, false, true, true };
	stack_project::Stack<double> first{ data, 4 }, second{ data, 6 }, 
		first_res{ data, 5 }, second_res{ data, 7 };
	stack_project::Stack<bool> b_first{ b_data, 4 }, b_second{ b_data, 6 },
		b_first_res{ b_data, 5 }, b_second_res{ b_data, 7 };
	first.push(-7.5);
	second.push(1.29);
	b_first.push(false);
	b_second.push(true);
	if (first == first_res && second == second_res &&
		b_first == b_first_res && b_second == b_second_res) { 
		return true;
	}
	std::cout << "Push test failed." << std::endl;
	return false;
}

bool Tests() {
	size_t number_of_fails = 0;
	if (!EqualityOperatorTest())
		++number_of_fails;
	if (!InequalityOperatorTest())
		++number_of_fails;
	if (!SizeTest())
		++number_of_fails;
	if (!CapacityTest())
		++number_of_fails;
	if (!IsEmptyTest())
		++number_of_fails;
	if (!TopTest())
		++number_of_fails;
	if (!PopTest())
		++number_of_fails;
	if (!PushTest())
		++number_of_fails;
	if (number_of_fails == 0) {
		std::cout << "Everything is fine." << std::endl;
		return true;
	}
	std::cout << "Number of failed tests: " << number_of_fails << '.' << std::endl;
	return false;
}