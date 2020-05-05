#include <gtest/gtest.h>

#include <src/for_each_in_tuple.hpp>

#include <string>
#include <tuple>

namespace
{
template <typename T>
typename std::enable_if_t<std::is_convertible_v<T, std::string>, std::string>
ToString(T && value)
{
  return std::forward<T>(value);
}

template <typename T>
typename std::enable_if_t<!std::is_convertible_v<T, std::string>, std::string>
ToString(T && value)
{
  return std::to_string(std::forward<T>(value));
}

template <typename... Types>
constexpr std::array<int, sizeof...(Types)> TupleToArray(
    const std::tuple<Types...> & tuple)
{
  std::array<int, sizeof...(Types)> result{};
  size_t i = 0;
  auto foo = [&result, &i](auto && item) {
    result[i] = item;
    ++i;
  };

  gmoryes::ForEachInTuple(std::move(foo), tuple);
  return result;
}
}  // namespace

TEST(Helpers, ForEachInTuple_NonVoidCallback)
{
  std::tuple<> a;
  std::tuple<int, int> tuple = {1, 2};
  std::vector<std::string> string_items;
  gmoryes::ForEachInTuple([](auto&& item) {
    return item * item;
  }, tuple);

  const std::tuple<int, int> answer = {1, 4};
  EXPECT_EQ(tuple, answer);
}

TEST(Helpers, ForEachInTuple_VoidCallback)
{
  std::tuple<int, double, std::string> tuple = {1, 2.0, "333"};
  std::vector<std::string> string_items;
  gmoryes::ForEachInTuple([&string_items](auto&& item) {
    string_items.push_back(ToString(item));
  }, tuple);

  const std::vector<std::string> answer = {"1", "2.000000", "333"};
  EXPECT_EQ(string_items, answer);
}

TEST(Helpers, ForEachInTuple_Constexpr)
{
  constexpr std::tuple<int, int, int> tuple{8, 13, 21};
  constexpr std::array<int, 3> answer{8, 13, 21};

  constexpr auto result = TupleToArray(tuple);
  static_assert(answer[0] == result[0]);
  static_assert(answer[1] == result[1]);
  static_assert(answer[2] == result[2]);
}
