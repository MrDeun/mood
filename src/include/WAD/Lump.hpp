#pragma once
#include <cstdint>
#include <vector>

#include "Lump_Header.hpp"

namespace WAD {

struct Lump {
  Lump_Header header;
  std::vector<uint8_t> data;
  void populate_data(const std::vector<uint8_t> &wad_data);
};

} // namespace WAD
