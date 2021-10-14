#ifndef STACK_PROJECT_STACK_INCLUDE_STACK_H_
#define STACK_PROJECT_STACK_INCLUDE_STACK_H_

#include <cstddef>

namespace stack_project {

	template <class T>
	class Stack {
	public:
		const size_t InitialCapacity = 32;
		const size_t MemoryMultiplier = 2;

		Stack();
		Stack(const T* data, size_t size);
		Stack(const Stack<T>& other);
		Stack(Stack<T>&& other);

		Stack<T>& operator=(const Stack<T>& other);
		Stack<T>& operator=(Stack<T>&& other);

		~Stack();

		void push(T data);
		T pop();
		T top() const;
		size_t size() const;
		size_t capacity() const;
		bool is_empty() const;

		bool operator==(const Stack<T>& other) const;
		bool operator!=(const Stack<T>& other) const;

	private:
		void data_realloc();

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

		Stack();
		Stack(const bool* data, size_t size);
		Stack(const Stack<bool>& other);
		Stack(Stack<bool>&& other);

		Stack<bool>& operator=(const Stack<bool>& other);
		Stack<bool>& operator=(Stack<bool>&& other);

		~Stack();

		void push(bool data);
		bool pop();
		bool top() const;
		size_t size() const;
		size_t capacity() const;
		bool is_empty() const;

		bool operator==(const Stack<bool>& other) const;
		bool operator!=(const Stack<bool>& other) const;

		size_t get_byte_capacity() const;

	private:
		void data_realloc();

		unsigned char* data_;
		size_t capacity_;
		size_t size_;
	};
	
} // namespace stack_project

#endif // STACK_PROJECT_STACK_INCLUDE_STACK_H_