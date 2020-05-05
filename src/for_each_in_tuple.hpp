#pragma once

#include <src/return_type.hpp>

#include <array>
#include <tuple>

namespace gmoryes
{
namespace details
{
template <typename Callback, typename... TupleTypes, std::size_t... I>
constexpr void IterateTuple(Callback && callback,
                            std::tuple<TupleTypes...> & tuple,
                            std::index_sequence<I...>)
{
  using AnyElementType = decltype(std::get<0>(tuple));
  if constexpr (ReturnType<Callback, AnyElementType>::IsVoid)
    (callback(std::get<I>(tuple)), ...);
  else
    ((std::get<I>(tuple) = callback(std::get<I>(tuple))), ...);
}

template <typename Callback, typename... TupleTypes, std::size_t... I>
constexpr void IterateTuple(Callback && callback,
                            const std::tuple<TupleTypes...> & tuple,
                            std::index_sequence<I...>)
{
  using AnyElementType = decltype(std::get<0>(tuple));
  static_assert(ReturnType<Callback, AnyElementType>::IsVoid,
                "Try to apply non void function to const tuple");

  (callback(std::get<I>(tuple)), ...);
}

template <typename Callback, typename Tuple>
constexpr void ForEachInTupleImpl(Callback && callback, Tuple && tuple)
{
  constexpr std::size_t tuple_size =
      std::tuple_size_v<std::decay_t<decltype(tuple)>>;
  if (tuple_size == 0)
    return;

  constexpr auto ids = std::make_index_sequence<tuple_size>{};

  details::IterateTuple(std::forward<Callback>(callback), tuple, ids);
}
}  // namespace details

template <typename Callback, typename... TupleTypes>
constexpr void ForEachInTuple(Callback && callback,
                              std::tuple<TupleTypes...> & tuple)
{
  details::ForEachInTupleImpl(std::forward<Callback>(callback),
                              std::forward<decltype(tuple)>(tuple));
}

template <typename Callback, typename... TupleTypes>
constexpr void ForEachInTuple(Callback && callback,
                              const std::tuple<TupleTypes...> & tuple)
{
  details::ForEachInTupleImpl(std::forward<Callback>(callback),
                              std::forward<decltype(tuple)>(tuple));
}
}  // namespace gmoryes
