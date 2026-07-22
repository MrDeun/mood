#include "../include/WAD.hpp"

#include <cstring>
#include <stdexcept>
namespace WAD {
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

[[nodiscard]] std::vector<WAD::Lump_Header> read_all_lumps(const std::vector<uint8_t>& wad_data,const WAD::Header& header){
    
    std::vector<WAD::Lump_Header> lumps(header.lumps_count);

    for (size_t i=0;i<header.lumps_count;i++) {
        static_assert(sizeof(WAD::Lump_Header)==16);
        const WAD::Lump_Header* lump_ptr = reinterpret_cast<const WAD::Lump_Header*>(wad_data.data() + header.directory_offset + i * sizeof(WAD::Lump_Header));
        lumps.at(i) = *lump_ptr;
    }

    return lumps;
}

[[nodiscard]] std::vector<Lump> convert_headers_to_full(const std::vector<uint8_t>& wad_data,const std::vector<WAD::Lump_Header>& _headers){
    std::vector<Lump> lumps;
    for (const auto& h : _headers) {
        Lump new_lump;
        new_lump.header = h;
        new_lump.populate_data(wad_data);
        lumps.push_back(new_lump);
    }
    return lumps;
}

WADFile::WADFile(const std::filesystem::path &path){
    std::ifstream stream(path, std::ios::binary | std::ios::ate);

    auto size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!stream.read(reinterpret_cast<char *>(buffer.data()), size)) {
      fmt::println("Error: Failure to read from {}", path.c_str());
    }
    _header = Header::parse(buffer);
    // fmt::println("{}", header.iden_to_string());
    // fmt::println("Total lumps: {}", header.lumps_count);
    // fmt::println("Directory offset at: {:X}", header.directory_offset);

    auto lump_headers = read_all_lumps(buffer, _header);
    _lumps = convert_headers_to_full(buffer, std::move(lump_headers));
}
nlohmann::json WADFile::to_json() const {
    nlohmann::json j;
    j["header"] = {
        {"identity",_header.iden_to_string()},
        {"lump_count",_header.lumps_count},
        {"directory_offset",_header.directory_offset},
    };

    for (size_t i=0 ;i<_lumps.size();++i) {
        const auto& lump = _lumps.at(i);
        j["lumps"][i]["header"] = {
            {"file_pos",lump.header.file_pos},
            {"size",lump.header.size},
            {"name",lump.header.name_to_string()},
        };
        // j["lumps"][i]["data"] = lump.data;
    }

    return j;
}


void Lump::populate_data(const std::vector<uint8_t>& _data){
 auto lump_size = header.size;
 auto location = header.file_pos;
 data.resize(lump_size);
 std::memcpy(data.data(), _data.data()+location, lump_size);
}
}



