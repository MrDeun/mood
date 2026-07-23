#include "../include/WAD.hpp"
#include "Errors.hpp"
#include "SFML/Graphics/Color.hpp"
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
  assert(pallete_data.size() % 256 * 3 ==
         0); // Assertion that we have n*256(size of pallete)*3(three bytes per
             // color)
  const auto pallete_count = pallete_data.size() / 256 * 3;
  constexpr size_t pallete_size = 256 * 3;

  for (size_t i = 0; i < pallete_count; i++) {
    const auto chunk = pallete_data.data() + i * pallete_size;
    std::array<sf::Color, 256> pallete;
    std::memcpy(pallete.data(), chunk, pallete_size);
    palletes.push_back(std::move(pallete));
  }

  return palletes;
}

}; // namespace WAD