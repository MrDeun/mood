
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "WAD/WADFile.hpp"
#include "fmt/core.h"
#include "vendors/CLI/CLI11.hpp"

namespace fs = std::filesystem;
struct Globals {
  fs::path wad_path;
};

Globals globals{.wad_path = ""};

int main(int argc, char **argv) {
  CLI::App app{"Mood - Doom source port for the funnies"};
  argv = app.ensure_utf8(argv);

  app.add_option("-f,--file", globals.wad_path, "Assign wad file to load");

  CLI11_PARSE(app, argc, argv);

  if (globals.wad_path.empty()) {
    fmt::println("Error: Path to a valid WAD file must be assigned!");
    return -1;
  }
  const auto wad_map = WAD::WADFile(globals.wad_path).to_map();
  const auto &pallete_data = wad_map.at("PLAYPAL");
  std::array<sf::Color, 256> pallete{};
  for (size_t i = 0; i < 256 * 3; i += 3) {
    const auto r = pallete_data.at(i);
    const auto g = pallete_data.at(i + 1);
    const auto b = pallete_data.at(i + 2);

    pallete.at(i / 3) = {r, g, b};
  }

  sf::RectangleShape rec{{100, 100}};
  rec.setOutlineColor(sf::Color::Black);
  rec.setOutlineThickness(2.f);
  sf::RenderWindow window(sf::VideoMode({32 * 16, 32 * 16}),
                          "Pallete from WAD file");

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();
    for (size_t y = 0; y < 16; y++) {
      for (size_t x = 0; x < 16; x++) {
        const auto color = pallete.at(x + y * 16);
        rec.setPosition({32.f * x, 32.f * y});
        rec.setFillColor(color);
        window.draw(rec);
      }
    }
    window.display();
  }

  return 0;
}
