#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace WAD {

struct Header {
  static constexpr auto IDEN_LIMIT = 4;
  using Iden_STR = std::array<char, IDEN_LIMIT>;
  Iden_STR identity;
  int32_t lumps_count;
  int32_t directory_offset;

  [[nodiscard]] std::string iden_to_string() const {
    size_t len = 0;
    while (len < identity.size() && identity[len] != '\0')
      ++len;
    return std::string(identity.data(), len);
  }

  static Header parse(const std::vector<uint8_t> &data);
};

}
