
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "WAD.hpp"
#include "WAD/WADFile.hpp"
#include "fmt/core.h"
#include "vendors/CLI/CLI11.hpp"

namespace fs = std::filesystem;
struct Globals {
  fs::path wad_path;
  sf::Font font;
};

Globals globals{.wad_path = "",
                .font{fs::path("./resources/fonts/jetbrains.ttf")}};

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
  const auto palletes = std::get<WAD::Palletes>(WAD::extract_pallets(wad_map));
  sf::RectangleShape rec{{100, 100}};
  sf::RectangleShape background({300, 50});
  background.setFillColor({0,0,0,128});
  rec.setOutlineColor(sf::Color::Black);
  rec.setOutlineThickness(2.f);
  sf::RenderWindow window(sf::VideoMode({75 * 16, 75 * 16}),
                          "Pallete from WAD file");
  sf::Text text(globals.font);
  text.setPosition({10, 10});
  int current_pallete_index = 0;
  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (event->is<sf::Event::KeyPressed>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
          current_pallete_index = current_pallete_index - 1;
          if (current_pallete_index < 0) {
            current_pallete_index = static_cast<int>(palletes.size()) - 1;
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
          current_pallete_index = (current_pallete_index + 1) % palletes.size();
        }
      }
    }

    const auto &pallete = palletes.at(current_pallete_index);

    window.clear();

    for (size_t y = 0; y < 16; y++) {
      for (size_t x = 0; x < 16; x++) {
        const auto color = pallete.at(x + y * 16);
        rec.setPosition({75.f * x, 75.f * y});
        rec.setFillColor(color);
        window.draw(rec);
      }
    }
    text.setString(fmt::format("Pallete no. {}", current_pallete_index + 1));
    window.draw(background);
    window.draw(text);
    window.display();
  }

  return 0;
}
