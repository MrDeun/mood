#include "../include/WAD/Header.hpp"

#include <cstring>
#include <stdexcept>

namespace WAD {
Header Header::parse(const std::vector<uint8_t> &data) {
  if (data.size() < sizeof(Header)) {
    throw std::runtime_error("File too small to contain a WAD header");
  }

  Header header{};
  std::memcpy(&header, data.data(), sizeof(Header));

  if (std::strncmp(header.identity.data(), "IWAD", 4) != 0 &&
      std::strncmp(header.identity.data(), "PWAD", 4) != 0) {
    throw std::runtime_error("Not a valid WAD file (bad magic)");
  }

  return header;
}
} // namespace WAD
