#include <gtest/gtest.h>

#include "../include/stack_impl.h"

namespace {

using stack_project::Stack;

TEST(StackTest, DefaultConstructor) {
  Stack<int> stack;
  EXPECT_EQ(0, stack.size());
}

TEST(StackTest, ConstructorFromArray) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> stack{data, size};
  Stack<bool> b_stack{b_data, size};
  EXPECT_EQ(size, stack.size());
  EXPECT_EQ(size, b_stack.size());
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(data[size - i - 1], stack.top());
    EXPECT_EQ(b_data[size - i - 1], b_stack.top());
    stack.pop();
    b_stack.pop();
  }
}

TEST(StackTest, CopyConstructor) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> other_stack{data, size}, stack{other_stack};
  Stack<bool> other_b_stack{b_data, size}, b_stack{other_b_stack};
  EXPECT_EQ(other_stack, stack);
  EXPECT_EQ(other_b_stack, b_stack);
}

TEST(StackTest, MoveConstructor) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> other_stack{data, size}, other_stack_copy{other_stack},
      stack{std::move(other_stack)};
  Stack<bool> other_b_stack{b_data, size}, other_b_stack_copy{other_b_stack},
      b_stack{std::move(other_b_stack)};
  EXPECT_EQ(other_stack_copy, stack);
  EXPECT_EQ(other_b_stack_copy, b_stack);
}

TEST(StackTest, CopyAssignmentOperator) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> other_stack{data, size}, stack;
  Stack<bool> other_b_stack{b_data, size}, b_stack;
  stack = other_stack;
  b_stack = other_b_stack;
  EXPECT_EQ(other_stack, stack);
  EXPECT_EQ(other_b_stack, b_stack);
}

TEST(StackTest, MoveAssignmentOperator) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> other_stack{data, size}, other_stack_copy{other_stack}, stack;
  Stack<bool> other_b_stack{b_data, size}, other_b_stack_copy{other_b_stack},
      b_stack;
  stack = std::move(other_stack);
  b_stack = std::move(other_b_stack);
  EXPECT_EQ(other_stack_copy, stack);
  EXPECT_EQ(other_b_stack_copy, b_stack);
}

TEST(StackTest, Push) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> other_stack{data, size}, stack{data, size - 1};
  Stack<bool> other_b_stack{b_data, size}, b_stack{b_data, size - 1};
  stack.push(other_stack.top());
  b_stack.push(other_b_stack.top());
  EXPECT_EQ(other_stack, stack);
  EXPECT_EQ(other_b_stack, b_stack);
}

TEST(StackTest, Pop) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> other_stack{data, size - 1}, stack{data, size};
  Stack<bool> other_b_stack{b_data, size - 1}, b_stack{b_data, size};
  stack.pop();
  b_stack.pop();
  EXPECT_EQ(other_stack, stack);
  EXPECT_EQ(other_b_stack, b_stack);
}

TEST(StackTest, Top) {
  const size_t size = 3;
  const int new_top = 4;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> stack{data, size};
  Stack<bool> b_stack{b_data, size};
  EXPECT_EQ(data[size - 1], stack.top());
  stack.top() = new_top;
  EXPECT_EQ(new_top, stack.top());
  EXPECT_EQ(b_data[size - 1], b_stack.top());
}

TEST(StackTest, Size) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> stack{data, size};
  Stack<bool> b_stack{b_data, size};
  EXPECT_EQ(size, stack.size());
  EXPECT_EQ(size, b_stack.size());
}

TEST(StackTest, Capacity) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> empty_stack, stack{data, size};
  Stack<bool> b_stack{b_data, size};
  EXPECT_EQ(empty_stack.InitialCapacity, stack.capacity());
  EXPECT_EQ(stack.InitialCapacity, stack.capacity());
  EXPECT_EQ(b_stack.InitialCapacity, b_stack.capacity());
  const size_t big_size = 40;
  int big_data[big_size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  Stack<int> big_stack{big_data, big_size};
  EXPECT_EQ(2 * big_stack.InitialCapacity, big_stack.capacity());
}

TEST(StackTest, IsEmpty) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> empty_stack, stack{data, size};
  Stack<bool> b_stack{b_data, size};
  EXPECT_EQ(true, empty_stack.is_empty());
  EXPECT_EQ(false, stack.is_empty());
  EXPECT_EQ(false, b_stack.is_empty());
}

TEST(StackTest, EqualityOperator) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> lhs{data, size}, rhs{data, size};
  Stack<bool> b_lhs{b_data, size}, b_rhs{b_data, size - 1};
  EXPECT_TRUE(lhs == rhs);
  EXPECT_FALSE(b_lhs == b_rhs);
}

TEST(StackTest, InequalityOperator) {
  const size_t size = 3;
  int data[size] = {5, 6, 3};
  bool b_data[size] = {false, true, true};
  Stack<int> lhs{data, size}, rhs{data, size - 1};
  Stack<bool> b_lhs{b_data, size}, b_rhs{b_data, size};
  EXPECT_TRUE(lhs != rhs);
  EXPECT_FALSE(b_lhs != b_rhs);
}

}  // namespace

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}