#include <gtest/gtest.h>

#include <src/is_optional.hpp>

#include <optional>
#include <vector>

TEST(Traits, IsOptional_1)
{
  constexpr std::optional<int> value;
  static_assert(gmoryes::IsOptional(value));
}

TEST(Traits, IsOptional_2)
{
  constexpr int value = 42;
  static_assert(!gmoryes::IsOptional(value));
}

TEST(Traits, IsOptional_RunTimeTests)
{
  {
    std::optional<int> optional{10};
    int value{20};

    EXPECT_TRUE(gmoryes::IsOptional(optional));
    EXPECT_FALSE(gmoryes::IsOptional(value));
  }

  {
    std::optional<std::vector<int>> optional_vector;
    EXPECT_TRUE(gmoryes::IsOptional(std::move(optional_vector)));
  }
  {
    std::optional<std::vector<int>> optional_vector;
    const auto & optional_vector_ref = optional_vector;
    EXPECT_TRUE(gmoryes::IsOptional(optional_vector_ref));
  }
}
