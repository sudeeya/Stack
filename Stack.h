#ifndef STACK_STACK_H_
#define STACK_STACK_H_

#include <cstddef>

struct Stack {
	Stack();
	Stack(const double* data, const size_t size);
	Stack(const Stack& other);
	Stack(Stack&& other);

	Stack& operator=(const Stack& other);
	Stack& operator=(Stack&& other);

	~Stack();

	void push(const double data);
	double pop();
	double peek() const;
	size_t size() const;
	size_t capacity() const;
	bool isEmpty() const;

	bool operator==(const Stack& other) const;
	bool operator!=(const Stack& other) const;

	size_t getInitialCapacity();
	size_t getMemoryMultiplier();

	double* data_;
	size_t capacity_;
	size_t size_;
};

#endif
