#pragma once
#include <array>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <fmt/core.h>
#include "../vendors/nlohmann_json/json.hpp"
namespace WAD {

struct Header {
  static constexpr auto IDEN_LIMIT = 4;
  using Iden_STR = std::array<char, IDEN_LIMIT>;
  Iden_STR identity;
  int32_t lumps_count;
  int32_t directory_offset;

  [[nodiscard]] std::string iden_to_string() const {
    size_t len = 0;
    while (len < identity.size() && identity[len] != '\0')
      ++len;
    return std::string(identity.data(), len);
  }

  static Header parse(const std::vector<uint8_t> &data);
};

struct Lump_Header {
  static constexpr auto NAME_LIMIT = 8;
  using Name_STR = std::array<char, NAME_LIMIT>;

  int32_t file_pos;
  int32_t size;
  std::array<char, NAME_LIMIT> name;
  [[nodiscard]] std::string name_to_string() const {
    size_t len = 0;
    while (len < name.size() && name[len] != '\0')
      ++len;
    return std::string(name.data(), len);
  }
};

struct Lump {
  Lump_Header header;
  std::vector<uint8_t> data;
  void populate_data(const std::vector<uint8_t> &wad_data);
};
[[nodiscard]] std::vector<WAD::Lump_Header>
read_all_lumps(const std::vector<uint8_t> &wad_data, const WAD::Header &header);

[[nodiscard]] std::vector<WAD::Lump>
convert_headers_to_full(const std::vector<uint8_t> &,
                        const std::vector<WAD::Lump_Header> &);

struct WADFile {
  WADFile() = delete;
  std::vector<Lump> _lumps{};
  Header _header{};

  WADFile(const std::filesystem::path &path);

  [[nodiscard]] nlohmann::json to_json() const;
};



}; // namespace WAD