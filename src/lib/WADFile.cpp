#include "../include/WAD/WADFile.hpp"
#include "../include/WAD/utils.hpp"
#include "WAD.hpp"

#include <fmt/core.h>
#include <fstream>
#include <unordered_map>

namespace WAD {
WADFile::WADFile(const std::filesystem::path &path) {
  std::ifstream stream(path, std::ios::binary | std::ios::ate);

  auto size = stream.tellg();
  stream.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(size);
  if (!stream.read(reinterpret_cast<char *>(buffer.data()), size)) {
    fmt::println("Error: Failure to read from {}", path.c_str());
  }
  header = Header::parse(buffer);

  auto lump_headers = read_all_lumps(buffer, header);
  lumps = convert_headers_to_full(buffer, lump_headers);
}

LumpMap WADFile::to_map() const {
  // CAUTION! Possible lost of map data!
  LumpMap map;
  for (const auto &l : lumps) {
    map.emplace(l.header.name_to_string(), l.data);
  }
  return map;
}

nlohmann::json WADFile::to_json() const {
  nlohmann::json j;
  j["header"] = {{"identity", header.iden_to_string()},
                 {"lump_count", header.lumps_count},
                 {"directory_offset", header.directory_offset}};

  for (size_t i = 0; i < lumps.size(); ++i) {
    const auto &lump = lumps.at(i);
    j["lumps"][i]["header"] = {{"file_pos", lump.header.file_pos},
                               {"size", lump.header.size},
                               {"name", lump.header.name_to_string()}};
    // j["lumps"][i]["data"] = lump.data;
  }

  return j;
}
} // namespace WAD
