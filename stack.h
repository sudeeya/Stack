#ifndef STACK_PROJECT_STACK_H_
#define STACK_PROJECT_STACK_H_

#include <cstddef>
#include <cmath>
#include <iostream>

namespace stack_project {

	template <class T>
	class Stack {
	public:
		const size_t InitialCapacity = 32;
		const size_t MemoryMultiplier = 2;

		Stack() : capacity_(InitialCapacity), size_(0) {
			data_ = new T[capacity_];
		}
		Stack(const T* data, size_t size) : capacity_(InitialCapacity), size_(size) {
			while (size_ > capacity_)
				capacity_ *= MemoryMultiplier;
			data_ = new T[capacity_];
			for (size_t i = 0; i < size_; ++i)
				data_[i] = data[i];
		}
		Stack(const Stack<T>& other) : capacity_(other.capacity_), size_(other.size_) {
			data_ = new T[capacity_];
			for (size_t i = 0; i < size_; ++i)
				data_[i] = other.data_[i];
		}
		Stack(Stack<T>&& other) : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
			other.data_ = nullptr;
		}

		Stack<T>& operator=(const Stack<T>& other) {
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
		Stack<T>& operator=(Stack<T>&& other) {
			size_ = other.size_;
			capacity_ = other.capacity_;
			data_ = other.data_;
			other.data_ = nullptr;
			return *this;
		}

		~Stack() {
			delete[] data_;
		}

		void push(T data) {
			if (size_ == capacity_)
				data_realloc();
			data_[size_] = data;
			++size_;
		}
		T pop() {
			--size_;
			return data_[size_];
		}
		T top() const {
			return data_[size_ - 1];
		}
		size_t size() const {
			return size_;
		}
		size_t capacity() const {
			return capacity_;
		}
		bool is_empty() const {
			if (size_ == 0)
				return true;
			return false;
		}

		bool operator==(const Stack<T>& other) const {
			if (size_ != other.size_)
				return false;
			for (size_t i = 0; i < size_; ++i)
				if (data_[i] != other.data_[i])
					return false;
			return true;
		}
		bool operator!=(const Stack<T>& other) const {
			return !(*this == other);
		}

	private:
		void data_realloc() {
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

		T* data_;
		size_t capacity_;
		size_t size_;
	};
	
	template <>
	class Stack<bool> {
	public:
		const size_t InitialCapacity = 32;
		const size_t MemoryMultiplier = 2;
		const size_t SizeOfChar = 8;

		Stack() : capacity_(InitialCapacity), size_(0) {
			size_t byte_capacity = get_byte_capacity();
			data_ = new unsigned char[byte_capacity];
			for (size_t i = 0; i < byte_capacity; ++i)
				data_[i] = 0;
		}
		Stack(const bool* data, size_t size) : capacity_(InitialCapacity), size_(size) {
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
		Stack(const Stack<bool>& other) : capacity_(other.capacity_), size_(other.size_) {
			size_t byte_capacity = get_byte_capacity();
			data_ = new unsigned char[byte_capacity];
			for (size_t i = 0; i < byte_capacity; ++i)
				data_[i] = other.data_[i];
		}
		Stack(Stack<bool>&& other) : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
			other.data_ = nullptr;
		}

		Stack<bool>& operator=(const Stack<bool>& other) {
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
		Stack<bool>& operator=(Stack<bool>&& other) {
			size_ = other.size_;
			capacity_ = other.capacity_;
			data_ = other.data_;
			other.data_ = nullptr;
			return *this;
		}

		~Stack() {
			delete[] data_;
		}

		void push(bool data) {
			if (size_ == capacity_)
				data_realloc();
			if (data) {
				size_t full_chars = size_ / SizeOfChar;
				size_t place = size_ - full_chars * SizeOfChar;
				data_[full_chars] ^= (char)pow(2, SizeOfChar - place - 1);
			}
			++size_;
		}
		bool pop() {
			size_t full_chars = size_ / SizeOfChar;
			size_t place = size_ - full_chars * SizeOfChar;
			unsigned char tmp = data_[full_chars];
			tmp &= ~(char)pow(2, SizeOfChar - place);
			--size_;
			if (data_[full_chars] != tmp) {
				data_[full_chars] ^= (char)pow(2, SizeOfChar - place);
				return true;
			}
			return false;
		}
		bool top() const {
			size_t full_chars = size_ / SizeOfChar;
			size_t place = size_ - full_chars * SizeOfChar;
			unsigned char tmp = data_[full_chars];
			tmp &= ~(char)pow(2, SizeOfChar - place);
			if (data_[full_chars] != tmp) {
				return true;
			}
			return false;
		}
		size_t size() const {
			return size_;
		}
		size_t capacity() const {
			return capacity_;
		}
		bool is_empty() const {
			if (size_ == 0)
				return true;
			return false;
		}

		bool operator==(const Stack<bool>& other) const {
			if (size_ != other.size_)
				return false;
			for (size_t i = 0; i < get_byte_capacity(); ++i)
				if (data_[i] != other.data_[i])
					return false;
			return true;
		}
		bool operator!=(const Stack<bool>& other) const {
			return !(*this == other);
		}

		size_t get_byte_capacity() const {
			if (capacity_ % SizeOfChar == 0)
				return capacity_ / SizeOfChar;
			return capacity_ / SizeOfChar + 1;
		}

	private:
		void data_realloc() {
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

		unsigned char* data_;
		size_t capacity_;
		size_t size_;
	};
	
} // namespace stack_project

#endif // STACK_PROJECT_STACK_H_