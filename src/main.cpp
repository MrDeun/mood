#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include "SFML/Window/Event.hpp"
#include "WAD.hpp"
#include "fmt/base.h"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <ios>
#include <iterator>

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
  rec.setOutlineThickness(0.5f);
  sf::RenderWindow window(sf::VideoMode({50 * 16, 50 * 16}),
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
        rec.setPosition({50.f * x, 50.f * y});
        rec.setFillColor(color);
        window.draw(rec);
      }
    }
    window.display();
  }

  return 0;
}
