#include "WAD.hpp"
#include "fmt/base.h"
#include <CLI/CLI.hpp>
#include <array>
#include <cstddef>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <ios>
#include <iterator>
namespace fs = std::filesystem;

int main(int argc, char **argv) {
  fs::path wad_path = "";
  CLI::App app{"Mood - Doom source port for the funnies"};
  argv = app.ensure_utf8(argv);

  app.add_option("-f,--file", wad_path, "Assign wad file to load");

  CLI11_PARSE(app, argc, argv);

  if (wad_path.empty()) {
    fmt::println("Error: Path to a valid WAD file must be assigned!");
    return -1;
  } else {
    fmt::println("WAD path: {}", wad_path.c_str());
  }

  std::ifstream stream(wad_path, std::ios::binary | std::ios::ate);

  auto size = stream.tellg();
  stream.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(size);
  if (!stream.read(reinterpret_cast<char *>(buffer.data()), size)) {
    fmt::println("Error: Failure to read from {}", wad_path.c_str());
  }

  WAD::Header header = WAD::Header::parse(buffer);
  fmt::println("{}", header.identity);
  fmt::println("Total lumps: {}", header.lumps_count);
  fmt::println("Directory offset at: {:X}", header.directory_offset);

  WAD::Lump* lump = reinterpret_cast<WAD::Lump*>(buffer.data() + header.directory_offset);

  fmt::println("Name of the lump: {}",lump->name);
  fmt::println("Size of the lump: {}",lump->size);


  return 0;
}
