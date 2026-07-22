#include "../include/WAD/Lump.hpp"

#include <cstring>

namespace WAD {
void Lump::populate_data(const std::vector<uint8_t> &_data) {
  data.resize(header.size);
  std::memcpy(data.data(), _data.data() + header.file_pos, header.size);
}
} // namespace WAD
