#pragma once

#include <type_traits>
#include <utility>

namespace gmoryes
{
namespace details
{
template <typename Function, typename... Args>
constexpr auto Invoke(Function && function, Args &&... args)
    -> decltype(function(std::forward<Args>(args)...));
}  // namespace details

template <typename Function, typename... Args>
struct ReturnType
{
  using Type = decltype(
      details::Invoke(std::declval<Function>(), std::declval<Args>()...));

  static constexpr bool IsVoid = std::is_same_v<Type, void>;
};
}  // namespace gmoryes
