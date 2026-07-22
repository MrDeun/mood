#include "../include/WAD/utils.hpp"

#include <cstring>

namespace WAD {
std::vector<Lump_Header> read_all_lumps(const std::vector<uint8_t> &wad_data,
                                        const Header &header) {
  std::vector<Lump_Header> lumps(header.lumps_count);

  for (size_t i = 0; i < header.lumps_count; i++) {
    static_assert(sizeof(Lump_Header) == 16);
    const Lump_Header *lump_ptr = reinterpret_cast<const Lump_Header *>(
        wad_data.data() + header.directory_offset + i * sizeof(Lump_Header));
    lumps.at(i) = *lump_ptr;
  }

  return lumps;
}

std::vector<Lump>
convert_headers_to_full(const std::vector<uint8_t> &wad_data,
                        const std::vector<Lump_Header> &_headers) {
  std::vector<Lump> lumps;
  for (const auto &h : _headers) {
    Lump new_lump;
    new_lump.header = h;
    new_lump.populate_data(wad_data);
    lumps.push_back(new_lump);
  }
  return lumps;
}
} // namespace WAD
