#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>
namespace WAD {

struct Header {
  static constexpr auto IDEN_LIMIT = 4;
  std::array<char, IDEN_LIMIT> identity;
  int32_t lumps_count;
  int32_t directory_offset;

  static Header parse(const std::vector<uint8_t> &data) {
    if (data.size() < sizeof(Header)) {
      throw std::runtime_error("File too small to contain a WAD header");
    }

    Header header{};
    std::memcpy(&header, data.data(), sizeof(Header));

    // Validate magic
    if (std::strncmp(header.identity.data(), "IWAD", 4) != 0 &&
        std::strncmp(header.identity.data(), "PWAD", 4) != 0) {
      throw std::runtime_error("Not a valid WAD file (bad magic)");
    }

    return header;
  }
};

struct Lump {
  static constexpr auto NAME_LIMIT = 8;

  int32_t file_pos;
  int32_t size;
  std::array<char, NAME_LIMIT> name;
};

}; // namespace WAD