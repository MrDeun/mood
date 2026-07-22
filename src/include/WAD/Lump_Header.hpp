#pragma once
#include <array>
#include <cstdint>
#include <string>

namespace WAD {

struct Lump_Header {
  static constexpr auto NAME_LIMIT = 8;
  using Name_STR = std::array<char, NAME_LIMIT>;

  int32_t file_pos;
  int32_t size;
  std::array<char, NAME_LIMIT> name;

  [[nodiscard]] std::string name_to_string() const {
    size_t len = 0;
    while (len < name.size() && name[len] != '\0')
      ++len;
    return std::string(name.data(), len);
  }
};

}
