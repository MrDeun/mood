#pragma once
#include <cstdint>
#include <variant>
namespace Mood {
enum class Error : uint8_t { UNKNOWN, NO_LUMP_FOUND };

template <typename T> using Result = std::variant<T, Error>;

}; // namespace Mood
