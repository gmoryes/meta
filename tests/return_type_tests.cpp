#include <gtest/gtest.h>

#include <src/return_type.hpp>

#include <string>
#include <type_traits>

namespace
{
void VoidFunction(const std::string&);
int NonVoidFunction(int);
void VoidFunctionNoArgs();
void FunctionManyArgs(int, double, short);
}  // namespace

TEST(Traits, ReturnType)
{
  constexpr auto foo = [](auto && x) { return x; };

  static_assert(
      std::is_same_v<gmoryes::ReturnType<decltype(foo), int>::Type, int>);
  static_assert(
      std::is_same_v<gmoryes::ReturnType<decltype(foo), std::string>::Type,
                     std::string>);
  static_assert(
      std::is_same_v<gmoryes::ReturnType<decltype(foo), double>::Type, double>);
}

TEST(Traits, ReturnType_IsVoid)
{
  static_assert(
      gmoryes::ReturnType<decltype(VoidFunction), const std::string &>::IsVoid);
  static_assert(gmoryes::ReturnType<decltype(VoidFunctionNoArgs)>::IsVoid);
  static_assert(gmoryes::ReturnType<decltype(FunctionManyArgs), int, double,
                                    short>::IsVoid);
  static_assert(!gmoryes::ReturnType<decltype(NonVoidFunction), int>::IsVoid);
}
