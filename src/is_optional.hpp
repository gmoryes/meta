#include <optional>
#include <type_traits>

namespace gmoryes
{
namespace details
{
template <typename T>
struct IsOptional : std::false_type
{
};

template <typename T>
struct IsOptional<std::optional<T>> : std::true_type
{
};
}  // namespace details

template <typename T>
constexpr bool kIsOptional = details::IsOptional<std::decay_t<T>>::value;

template <typename T>
constexpr bool IsOptional(T&&) {
  return kIsOptional<T>;
}
}  // namespace gmoryes
