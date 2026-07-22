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

std::vector<uint8_t> read_wad_file(const fs::path &_path) {
  std::ifstream stream(_path, std::ios::binary | std::ios::ate);

  auto size = stream.tellg();
  stream.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(size);
  if (!stream.read(reinterpret_cast<char *>(buffer.data()), size)) {
    fmt::println("Error: Failure to read from {}", _path.c_str());
  }

  return buffer;
}

int main(int argc, char **argv) {
  CLI::App app{"Mood - Doom source port for the funnies"};
  argv = app.ensure_utf8(argv);

  app.add_option("-f,--file", globals.wad_path, "Assign wad file to load");

  CLI11_PARSE(app, argc, argv);

  if (globals.wad_path.empty()) {
    fmt::println("Error: Path to a valid WAD file must be assigned!");
    return -1;
  } else {
    fmt::println("WAD path: {}", globals.wad_path.c_str());
  }
  auto buffer = read_wad_file(globals.wad_path);
  WAD::Header header = WAD::Header::parse(buffer);
  fmt::println("{}", header.iden_to_string());
  fmt::println("Total lumps: {}", header.lumps_count);
  fmt::println("Directory offset at: {:X}", header.directory_offset);

  auto lump_headers = WAD::read_all_lumps(buffer, header);
  auto lumps = WAD::convert_headers_to_full(buffer, std::move(lump_headers));

  for (const auto& l : lumps) {
    assert(l.header.size == l.data.size());
    fmt::println("==================");
    fmt::println("NAME: {}",l.header.name_to_string());
    fmt::println("SIZE: {}",l.header.size);
  }

  return 0;
}
