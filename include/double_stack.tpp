#ifndef DOUBLE_STACK_TPP
#define DOUBLE_STACK_TPP

#include <algorithm>
#include <bit>
#include <cassert>
#include <iterator>
#include <limits>

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr double_stack<T>::double_stack(std::initializer_list<T> first,
                                        std::initializer_list<T> second)
    : data_() {
  ConstructFirst(first);
  ConstructSecond(second);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename Second>
constexpr double_stack<T>::double_stack(std::initializer_list<T> first,
                                        Second&& second)
    : data_() {
  ConstructFirst(first);
  ConstructSecond(std::forward<Second>(second));
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename First>
constexpr double_stack<T>::double_stack(First&& first,
                                        std::initializer_list<T> second)
    : data_() {
  ConstructFirst(std::forward<First>(first));
  ConstructSecond(second);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename First, typename Second>
constexpr double_stack<T>::double_stack(First&& first, Second&& second)
    : data_() {
  ConstructFirst(std::forward<First>(first));
  ConstructSecond(std::forward<Second>(second));
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename It, typename Second>
constexpr double_stack<T>::double_stack(It first_begin, It first_end,
                                        Second&& second)
    : data_() {
  ConstructFirst(first_begin, first_end);
  ConstructSecond(std::forward<Second>(second));
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename It>
constexpr double_stack<T>::double_stack(It first_begin, It first_end,
                                        std::initializer_list<T> second)
    : data_() {
  ConstructFirst(first_begin, first_end);
  ConstructSecond(second);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename First, typename It>
constexpr double_stack<T>::double_stack(First&& first, It second_begin,
                                        It second_end)
    : data_() {
  ConstructFirst(std::forward<First>(first));
  ConstructSecond(second_begin, second_end);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename It>
constexpr double_stack<T>::double_stack(std::initializer_list<T> first,
                                        It second_begin, It second_end)
    : data_() {
  ConstructFirst(first);
  ConstructSecond(second_begin, second_end);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename It1, typename It2>
constexpr double_stack<T>::double_stack(It1 first_begin, It1 first_end,
                                        It2 second_begin, It2 second_end)
    : data_() {
  ConstructFirst(first_begin, first_end);
  ConstructSecond(second_begin, second_end);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
               std::is_move_constructible_v<T> &&
               std::is_copy_assignable_v<T> && std::is_move_assignable_v<T>
constexpr double_stack<T>::double_stack(const double_stack& other)
    : data_(other.data_), size_first_(other.size_first_),
      size_second_(other.size_second_) {}

template <typename T>
  requires std::is_default_constructible_v<T> &&
               std::is_move_constructible_v<T> &&
               std::is_copy_assignable_v<T> && std::is_move_assignable_v<T>
constexpr double_stack<T>::double_stack(double_stack&& other)
    : data_(std::move(other.data_)), size_first_(other.size_first_),
      size_second_(other.size_second_) {
  other.data_.clear();
  other.size_first_ = 0;
  other.size_second_ = 0;
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr double_stack<T>&
double_stack<T>::operator=(const double_stack& other) {
  if (this != &other) {
    data_ = other.data_;
    size_first_ = other.size_first_;
    size_second_ = other.size_second_;
  }
  return *this;
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr double_stack<T>& double_stack<T>::operator=(double_stack&& other) {
  if (this != &other) {
    data_ = std::move(other.data_);
    size_first_ = other.size_first_;
    size_second_ = other.size_second_;
    other.data_.clear();
    other.size_first_ = 0;
    other.size_second_ = 0;
  }
  return *this;
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr auto&& double_stack<T>::top(this auto&& self, int num_pila) noexcept {
  assert(num_pila == NUM_PILA_FIRST || num_pila == NUM_PILA_SECOND);
  assert(!self.empty(num_pila) &&
         "Cannot use top() on an empty stack of a double stack");

  return std::forward_like<decltype(self)>(
      num_pila == NUM_PILA_FIRST
          ? self.data_[self.size_first_ - 1]
          : self.data_[self.data_.size() - self.size_second_]);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr bool double_stack<T>::empty(int num_pila) const noexcept {
  assert(num_pila == NUM_PILA_FIRST || num_pila == NUM_PILA_SECOND);
  return num_pila == NUM_PILA_FIRST ? size_first_ == 0 : size_second_ == 0;
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr typename double_stack<T>::size_type
double_stack<T>::size(int num_pila) const noexcept {
  assert(num_pila == NUM_PILA_FIRST || num_pila == NUM_PILA_SECOND);
  return num_pila == NUM_PILA_FIRST ? size_first_ : size_second_;
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
std::stack<T> double_stack<T>::copy_stack(int num_pila) const {
  assert(num_pila == NUM_PILA_FIRST || num_pila == NUM_PILA_SECOND);

  std::stack<T> stack_copy;
  if (num_pila == NUM_PILA_FIRST) {
    for (size_type i = 0; i < size_first_; ++i) {
      stack_copy.push(data_[i]);
    }
  } else {
    const size_type first_index = data_.size() - size_second_;
    for (size_type i = data_.size(); i > first_index;) {
      stack_copy.push(data_[--i]);
    }
  }
  return stack_copy;
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::push(const value_type& value, int num_pila) {
  assert(num_pila == NUM_PILA_FIRST || num_pila == NUM_PILA_SECOND);
  value_type staged(value);
  if (size_first_ + size_second_ == data_.size()) {
    const size_type old_size = data_.size();
    data_.resize(UpperTwoPower(size_first_ + size_second_ + 1));
    std::move_backward(data_.begin() + old_size - size_second_,
                       data_.begin() + old_size, data_.end());
  }

  if (num_pila == NUM_PILA_FIRST) {
    data_[size_first_] = std::move(staged);
    ++size_first_;
  } else {
    data_[data_.size() - size_second_ - 1] = std::move(staged);
    ++size_second_;
  }
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::push(value_type&& value, int num_pila) {
  assert(num_pila == NUM_PILA_FIRST || num_pila == NUM_PILA_SECOND);
  value_type staged(std::move(value));
  if (size_first_ + size_second_ == data_.size()) {
    const size_type old_size = data_.size();
    data_.resize(UpperTwoPower(size_first_ + size_second_ + 1));
    std::move_backward(data_.begin() + old_size - size_second_,
                       data_.begin() + old_size, data_.end());
  }

  if (num_pila == NUM_PILA_FIRST) {
    data_[size_first_] = std::move(staged);
    ++size_first_;
  } else {
    data_[data_.size() - size_second_ - 1] = std::move(staged);
    ++size_second_;
  }
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <class... Args>
constexpr typename double_stack<T>::reference
double_stack<T>::emplace(int num_pila, Args&&... args) {
  value_type value(std::forward<Args>(args)...);
  push(std::move(value), num_pila);
  return top(num_pila);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::pop(int num_pila) {
  assert(num_pila == NUM_PILA_FIRST || num_pila == NUM_PILA_SECOND);
  assert(!empty(num_pila) && "Cannot pop from an empty stack");
  if (num_pila == NUM_PILA_FIRST) {
    data_.erase(data_.begin() + size_first_ - 1);
    --size_first_;
  } else {
    data_.erase(data_.begin() + data_.size() - size_second_);
    --size_second_;
  }
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::swap(double_stack& other) {
  using std::swap;
  data_.swap(other.data_);
  swap(size_first_, other.size_first_);
  swap(size_second_, other.size_second_);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
[[nodiscard]] constexpr bool
double_stack<T>::operator==(const double_stack& other) const {
  if (size_first_ != other.size_first_ || size_second_ != other.size_second_) {
    return false;
  }

  const bool first_equal = std::equal(
      data_.begin(), data_.begin() + size_first_, other.data_.begin());
  if (!first_equal) {
    return false;
  }

  return std::equal(data_.end() - size_second_, data_.end(),
                    other.data_.end() - size_second_);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
[[nodiscard]] constexpr bool
double_stack<T>::operator!=(const double_stack& other) const {
  return !(*this == other);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename StackContainer>
constexpr void
double_stack<T>::ConstructFirst(std::stack<T, StackContainer> first) {
  PrepareFirst(first.size());

  size_type first_index = size_first_;
  while (!first.empty()) {
    --first_index;
    data_[first_index] = std::move(first.top());
    first.pop();
  }
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::ConstructFirst(std::initializer_list<T> first) {
  PrepareFirst(first.size());
  std::copy(first.begin(), first.end(), data_.begin());
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::ConstructFirst(container_type first) {
  PrepareFirst(first.size());
  std::move(first.begin(), first.end(), data_.begin());
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename It>
constexpr void double_stack<T>::ConstructFirst(It first_1, It last_1) {
  container_type values(first_1, last_1);
  ConstructFirst(std::move(values));
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename StackContainer>
constexpr void
double_stack<T>::ConstructSecond(std::stack<T, StackContainer> second) {
  PrepareSecond(second.size());

  size_type second_index = data_.size() - size_second_;
  while (!second.empty()) {
    data_[second_index] = std::move(second.top());
    second.pop();
    ++second_index;
  }
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void
double_stack<T>::ConstructSecond(std::initializer_list<T> second) {
  PrepareSecond(second.size());
  std::copy(second.begin(), second.end(), data_.begin() + size_first_);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::ConstructSecond(container_type second) {
  PrepareSecond(second.size());
  std::move(std::begin(second), std::end(second), data_.rbegin());
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
template <typename It>
constexpr void double_stack<T>::ConstructSecond(It first_2, It last_2) {
  container_type values(first_2, last_2);
  ConstructSecond(std::move(values));
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::PrepareFirst(size_type first) {
  size_first_ = first;
  data_.resize(size_first_);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr void double_stack<T>::PrepareSecond(size_type second) {
  size_second_ = second;

  size_type size_total = size_first_ + size_second_;
  size_type size_resize = UpperTwoPower(size_total);
  data_.resize(size_resize);
}

template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
constexpr typename double_stack<T>::size_type
double_stack<T>::UpperTwoPower(size_type num) const noexcept {
  const size_type highest_power_of_two =
      std::bit_floor(std::numeric_limits<size_type>::max());
  if (num > highest_power_of_two) {
    return num;
  }
  return std::bit_ceil(num == 0 ? 1 : num);
}

template <typename T>
constexpr void swap(double_stack<T>& first, double_stack<T>& second) {
  first.swap(second);
}

#endif // DOUBLE_STACK_TPP
