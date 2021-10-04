#include "Stack.h"
#include <cstdlib>
#include <cstddef>
#include <iostream>

Stack::Stack() : capacity_(getInitialCapacity()), size_(0) {
	data_ = (double*)malloc(capacity_ * sizeof(double));
	if (data_ == nullptr) {
		std::cout << "Error: memory allocation failed." << std::endl;
		exit(1);
	}
}

Stack::Stack(const double* data, const size_t size) : capacity_(getInitialCapacity()), size_(size) {
	while (size_ > capacity_)
		capacity_ *= getMemoryMultiplier();
	data_ = (double*)malloc(capacity_ * sizeof(double));
	if (data_ == nullptr) {
		std::cout << "Error: memory allocation failed." << std::endl;
		exit(1);
	}
	for (size_t i = 0; i < size_; ++i)
		data_[i] = data[i];
}

Stack::Stack(const Stack& other) : capacity_(other.capacity_), size_(other.size_) {
	data_ = (double*)malloc(capacity_ * sizeof(double));
	if (data_ == nullptr) {
		std::cout << "Error: memory allocation failed." << std::endl;
		exit(1);
	}
	for (size_t i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

Stack::Stack(Stack&& other) : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
	other.data_ = nullptr;
}

Stack& Stack::operator=(const Stack& other) {
	if (this == &other)
		return *this;
	free(data_);
	size_ = other.size_;
	capacity_ = other.capacity_;
	data_ = (double*)malloc(capacity_ * sizeof(double));
	if (data_ == nullptr) {
		std::cout << "Error: memory allocation failed." << std::endl;
		exit(1);
	}
	for (size_t i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
	return *this;
}

Stack& Stack::operator=(Stack&& other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	data_ = other.data_;
	other.data_ = nullptr;
	return *this;
}

Stack::~Stack() {
	free(data_);
}

void Stack::push(const double data) {
	if (size_ == capacity_) {
		capacity_ *= getMemoryMultiplier();
		data_ = (double*)realloc(data_, capacity_ * sizeof(double));
		if (data_ == nullptr) {
			std::cout << "Error: memory allocation failed." << std::endl;
			exit(1);
		}
	}
	data_[size_] = data;
	++size_;
}

double Stack::pop() {
	if (isEmpty()) {
		std::cout << "Error: stack is empty, it is impossible to pop." << std::endl;
		exit(1);
	}
	--size_;
	return data_[size_];
}

double Stack::peek() const {
	if (isEmpty()) {
		std::cout << "Error: stack is empty, it is impossible to peek." << std::endl;
		exit(1);
	}
	return data_[size_ - 1];
}

size_t Stack::size() const {
	return size_;
}

size_t Stack::capacity() const {
	return capacity_;
}

bool Stack::isEmpty() const {
	if (size_ == 0)
		return true;
	return false;
}

bool Stack::operator==(const Stack& other) const {
	if (size_ != other.size_)
		return false;
	if (capacity_ != other.capacity_)
		return false;
	for (size_t i = 0; i < size_; ++i)
		if (data_[i] != other.data_[i])
			return false;
	return true;
}

bool Stack::operator!=(const Stack& other) const {
	return !(*this == other);
}

size_t Stack::getInitialCapacity() {
	return 32;
}

size_t Stack::getMemoryMultiplier() {
	return 2;
}
