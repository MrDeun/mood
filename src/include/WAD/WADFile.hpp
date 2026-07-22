#pragma once
#include <filesystem>
#include <vector>

#include "Header.hpp"
#include "Lump.hpp"
#include "../vendors/nlohmann_json/json.hpp"

namespace WAD {

struct WADFile {
  WADFile() = delete;
  std::vector<Lump> _lumps{};
  Header _header{};

  WADFile(const std::filesystem::path &path);

  [[nodiscard]] nlohmann::json to_json() const;
};

}
