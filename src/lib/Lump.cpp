#include "../include/WAD/Lump.hpp"

#include <cstring>

namespace WAD {
void Lump::populate_data(const std::vector<uint8_t> &_data) {
  auto lump_size = header.size;
  auto location = header.file_pos;
  data.resize(lump_size);
  std::memcpy(data.data(), _data.data() + location, lump_size);
}
}
