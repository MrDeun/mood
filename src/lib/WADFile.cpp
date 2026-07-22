#include "../include/WAD/WADFile.hpp"
#include "../include/WAD/utils.hpp"

#include <fmt/core.h>
#include <fstream>

namespace WAD {
WADFile::WADFile(const std::filesystem::path &path) {
  std::ifstream stream(path, std::ios::binary | std::ios::ate);

  auto size = stream.tellg();
  stream.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(size);
  if (!stream.read(reinterpret_cast<char *>(buffer.data()), size)) {
    fmt::println("Error: Failure to read from {}", path.c_str());
  }
  _header = Header::parse(buffer);

  auto lump_headers = read_all_lumps(buffer, _header);
  _lumps = convert_headers_to_full(buffer, std::move(lump_headers));
}

nlohmann::json WADFile::to_json() const {
  nlohmann::json j;
  j["header"] = {{"identity", _header.iden_to_string()},
                 {"lump_count", _header.lumps_count},
                 {"directory_offset", _header.directory_offset}};

  for (size_t i = 0; i < _lumps.size(); ++i) {
    const auto &lump = _lumps.at(i);
    j["lumps"][i]["header"] = {{"file_pos", lump.header.file_pos},
                               {"size", lump.header.size},
                               {"name", lump.header.name_to_string()}};
  }

  return j;
}
}
