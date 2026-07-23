#pragma once
#include <cstdint>
#include <variant>
namespace Mood {
enum class Error : uint8_t { NO_ERROR, UNKNOWN, NO_LUMP_FOUND };

template <typename T> class Result {
private:
  std::variant<T, Error> object;

public:
  bool has_value() const noexcept {
    try {
      return std::holds_alternative<T>(object);
    } catch (...) {
      return false;
    }
  }

  T &value_or(const T &other) {
    try {
      return std::get<T>(object);
    } catch (...) {
      return other;
    }
  }

  explicit operator bool() const noexcept { return has_value(); }

  Result() = delete;
  Result(const Error &error) : object(error) {}
  Result(Error &&error) : object(std::move(error)) {}
  Result(const T &value) : object(value) {}
  Result(T &&value) : object(std::move(value)) {}

  //   Result &operator=(const Error &error) = default;
  //   Result &operator=(Error &&error) = default;
  //   Result &operator=(const T &value) = default;
  //   Result &operator=(T &&value) = default;

  [[nodiscard]] T &value() { return std::get<T>(object); }
  [[nodiscard]] Error &error() { return std::get<Error>(object); }
};

}; // namespace Mood
