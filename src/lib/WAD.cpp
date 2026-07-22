#include "../include/WAD.hpp"

#include <cstring>
#include <stdexcept>

WAD::Header WAD::Header::parse(const std::vector<uint8_t> &data) {
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

[[nodiscard]] std::vector<WAD::Lump_Header> WAD::read_all_lumps(const std::vector<uint8_t>& wad_data,const WAD::Header& header){
    
    std::vector<WAD::Lump_Header> lumps(header.lumps_count);

    for (size_t i=0;i<header.lumps_count;i++) {
        static_assert(sizeof(WAD::Lump_Header)==16);
        const WAD::Lump_Header* lump_ptr = reinterpret_cast<const WAD::Lump_Header*>(wad_data.data() + header.directory_offset + i * sizeof(WAD::Lump_Header));
        lumps.at(i) = *lump_ptr;
    }

    return lumps;
}

[[nodiscard]] std::vector<WAD::Lump> WAD::convert_headers_to_full(const std::vector<uint8_t>& wad_data, std::vector<WAD::Lump_Header>&& _headers){
    std::vector<WAD::Lump> lumps;
    for (const auto& h : _headers) {
        WAD::Lump new_lump;
        new_lump.header = h;
        new_lump.populate_data(wad_data);
        lumps.push_back(new_lump);
    }
    return lumps;
}


void WAD::Lump::populate_data(const std::vector<uint8_t>& _data){
 auto lump_size = header.size;
 auto location = header.file_pos;
 data.resize(lump_size);
 std::memcpy(data.data(), _data.data()+location, lump_size);
}


