#include "Errors.hpp"
#include "SFML/Graphics/Color.hpp"
#include "WAD/WADFile.hpp"
#include <vector>
namespace WAD {
using Palletes = std::vector<std::array<sf::Color, 256>>;

Mood::Result<Palletes> extract_pallets(const LumpMap &map);

}; // namespace WAD