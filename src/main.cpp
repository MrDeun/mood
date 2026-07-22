#include "WAD.hpp"
#include "fmt/base.h"
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
struct Globals{
  fs::path wad_path;
};

Globals globals {
  .wad_path=""
};

int main(int argc, char **argv) {
  CLI::App app{"Mood - Doom source port for the funnies"};
  argv = app.ensure_utf8(argv);

  app.add_option("-f,--file", globals.wad_path, "Assign wad file to load");

  CLI11_PARSE(app, argc, argv);

  if (globals.wad_path.empty()) {
    fmt::println("Error: Path to a valid WAD file must be assigned!");
    return -1;
  }
  
  auto wad = WAD::WADFile(globals.wad_path);
  auto j = wad.to_json();
  fmt::println("{}",j.dump());
  return 0;
}
