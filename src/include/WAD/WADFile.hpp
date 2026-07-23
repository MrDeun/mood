#pragma once
#include <filesystem>
#include <unordered_map>
#include <vector>

#include "../vendors/nlohmann_json/json.hpp"
#include "Header.hpp"
#include "Lump.hpp"

namespace WAD {
using LumpMap = std::unordered_map<std::string, std::vector<uint8_t>>;
struct WADFile {
  WADFile() = delete;
  std::vector<Lump> lumps{};
  Header header{};

  WADFile(const std::filesystem::path &path);
  [[nodiscard]] LumpMap to_map() const; // CAUTION! Possible lost of map data!
  [[nodiscard]] nlohmann::json to_json() const;
};

} // namespace WAD
