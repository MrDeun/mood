#include "../include/WAD.hpp"
#include "Errors.hpp"
#include "SFML/Graphics/Color.hpp"
#include "fmt/core.h"
#include "fmt/ranges.h"
#include <cassert>
#include <cstdint>
#include <exception>
#include <vector>

namespace WAD {
Mood::Result<Palletes> extract_pallets(const LumpMap &map) {
  if (map.find("PLAYPAL") == end(map)) {
    return Mood::Error::NO_LUMP_FOUND;
  }
  const auto &pallete_data = map.at("PLAYPAL");
  Palletes palletes;
  constexpr size_t pallete_size = 256 * 3;
  // Assertion that we have n*256(size of pallete)*3(three bytes per color)
  assert(pallete_data.size() % pallete_size == 0);
  const auto pallete_count = pallete_data.size() / (256 * 3);
  for (size_t i = 0; i < pallete_count; i++) {
    const auto offset = i * pallete_size;
    std::array<sf::Color, 256> pallete{};
    for (size_t j = 0; j < pallete_size-1; j += 3) {
      const auto r = pallete_data.at(j + offset);
      const auto g = pallete_data.at(j + offset + 1);
      const auto b = pallete_data.at(j + offset + 2);
      pallete.at(j / 3) = {r, g, b};
    }
    palletes.push_back(std::move(pallete));
  }
  return palletes;
}

}; // namespace WAD