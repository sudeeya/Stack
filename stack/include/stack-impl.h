#ifndef STACK_PROJECT_STACK_INCLUDE_STACK_IMPL_H_
#define STACK_PROJECT_STACK_INCLUDE_STACK_IMPL_H_

#include <cstddef>
#include "stack.h"

namespace stack_project {

	template <class T>
	Stack<T>::Stack() : capacity_(InitialCapacity), size_(0) {
		data_ = new T[capacity_];
	}

	template <class T>
	Stack<T>::Stack(const T* data, size_t size) : capacity_(InitialCapacity), size_(size) {
		while (size_ > capacity_)
			capacity_ *= MemoryMultiplier;
		data_ = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
			data_[i] = data[i];
	}

	template <class T>
	Stack<T>::Stack(const Stack<T>& other) : capacity_(other.capacity_), size_(other.size_) {
		data_ = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
	}

	template <class T>
	Stack<T>::Stack(Stack<T>&& other) : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
		other.data_ = nullptr;
	}

	template <class T>
	Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
		if (this == &other)
			return *this;
		delete[] data_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
		return *this;
	}
		
	template <class T>
	Stack<T>& Stack<T>::operator=(Stack<T>&& other) {
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = other.data_;
		other.data_ = nullptr;
		return *this;
	}

	template <class T>
	Stack<T>::~Stack() {
		delete[] data_;
	}

	template <class T>
	void Stack<T>::push(T data) {
		if (size_ == capacity_)
			data_realloc();
		data_[size_] = data;
		++size_;
	}
	
	template <class T>
	void Stack<T>::pop() {
		--size_;
	}
	
	template <class T>
	T& Stack<T>::top() {
		return data_[size_ - 1];
	}
	
	template <class T>
	size_t Stack<T>::size() const {
		return size_;
	}
	
	template <class T>
	size_t Stack<T>::capacity() const {
		return capacity_;
	}
	
	template <class T>
	bool Stack<T>::is_empty() const {
		if (size_ == 0)
			return true;
		return false;
	}

	template <class T>
	bool Stack<T>::operator==(const Stack<T>& other) const {
		if (size_ != other.size_)
			return false;
		for (size_t i = 0; i < size_; ++i)
			if (data_[i] != other.data_[i])
				return false;
		return true;
	}
	
	template <class T>
	bool Stack<T>::operator!=(const Stack<T>& other) const {
		return !(*this == other);
	}

	template <class T>
	void Stack<T>::data_realloc() {
		T* tmp;
		tmp = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
			tmp[i] = data_[i];
		capacity_ *= MemoryMultiplier;
		data_ = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
			data_[i] = tmp[i];
		delete[] tmp;
	}
	
	Stack<bool>::Stack() : capacity_(InitialCapacity), size_(0) {
		size_t byte_capacity = get_byte_capacity();
		data_ = new unsigned char[byte_capacity];
		for (size_t i = 0; i < byte_capacity; ++i)
			data_[i] = 0;
	}
	
	Stack<bool>::Stack(const bool* data, size_t size) : capacity_(InitialCapacity), size_(size) {
		while (size_ > capacity_)
			capacity_ *= MemoryMultiplier;
		size_t byte_capacity = get_byte_capacity();
		data_ = new unsigned char[byte_capacity];
		for (size_t i = 0; i < byte_capacity; ++i)
			data_[i] = 0;
		size_t data_index = 0;
		for (size_t i = 0; i < size_ / SizeOfChar + 1; ++i) {
			for (size_t j = 0; j < SizeOfChar; ++j) {
				data_[i] <<= 1;
				if (data[data_index] && data_index < size)
					data_[i] ^= 1;
				++data_index;
			}
		}
	}
	
	Stack<bool>::Stack(const Stack<bool>& other) : capacity_(other.capacity_), size_(other.size_) {
		size_t byte_capacity = get_byte_capacity();
		data_ = new unsigned char[byte_capacity];
		for (size_t i = 0; i < byte_capacity; ++i)
			data_[i] = other.data_[i];
	}
	
	Stack<bool>::Stack(Stack<bool>&& other) : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
		other.data_ = nullptr;
	}

	Stack<bool>& Stack<bool>::operator=(const Stack<bool>& other) {
		if (this == &other)
			return *this;
		delete[] data_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		size_t byte_capacity = get_byte_capacity();
		data_ = new unsigned char[byte_capacity];
		for (size_t i = 0; i < byte_capacity; ++i)
			data_[i] = other.data_[i];
		return *this;
	}
	
	Stack<bool>& Stack<bool>::operator=(Stack<bool>&& other) {
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = other.data_;
		other.data_ = nullptr;
		return *this;
	}

	Stack<bool>::~Stack() {
		delete[] data_;
	}

	void Stack<bool>::push(bool data) {
		if (size_ == capacity_)
			data_realloc();
		if (data) {
			size_t full_chars = size_ / SizeOfChar;
			size_t place = size_ - full_chars * SizeOfChar;
			data_[full_chars] ^= 1 << (SizeOfChar - place - 1);
		}
		++size_;
	}
	
	void Stack<bool>::pop() {
		--size_;
	}
	
	bool Stack<bool>::top() const {
		size_t full_chars = size_ / SizeOfChar;
		size_t place = size_ - full_chars * SizeOfChar;
		if (((data_[full_chars] >> (SizeOfChar - place)) & 1) == 1) {
			return true;
		}
		return false;
	}
	
	size_t Stack<bool>::size() const {
		return size_;
	}
	
	size_t Stack<bool>::capacity() const {
		return capacity_;
	}
	
	bool Stack<bool>::is_empty() const {
		if (size_ == 0)
			return true;
		return false;
	}

	bool Stack<bool>::operator==(const Stack<bool>& other) const {
		if (size_ != other.size_)
			return false;
		for (size_t i = 0; i < get_byte_capacity(); ++i)
			if (data_[i] != other.data_[i])
				return false;
		return true;
	}
	
	bool Stack<bool>::operator!=(const Stack<bool>& other) const {
		return !(*this == other);
	}

	size_t Stack<bool>::get_byte_capacity() const {
		if (capacity_ % SizeOfChar == 0)
			return capacity_ / SizeOfChar;
		return capacity_ / SizeOfChar + 1;
	}

	void Stack<bool>::data_realloc() {
		unsigned char* tmp;
		size_t old_byte_capacity = get_byte_capacity();
		tmp = new unsigned char[old_byte_capacity];
		for (size_t i = 0; i < old_byte_capacity; ++i)
			tmp[i] = data_[i];
	    capacity_ *= MemoryMultiplier;
		size_t new_byte_capacity = get_byte_capacity();
		data_ = new unsigned char[new_byte_capacity];
		for (size_t i = 0; i < new_byte_capacity; ++i)
			data_[i] = 0;
		for (size_t i = 0; i < old_byte_capacity; ++i)
			data_[i] = tmp[i];
		delete[] tmp;
	}
	
} // namespace stack_project

#endif // STACK_PROJECT_STACK_INCLUDE_STACK_IMPL_H_
