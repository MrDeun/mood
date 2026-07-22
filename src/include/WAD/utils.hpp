#pragma once
#include <cstdint>
#include <vector>

#include "Header.hpp"
#include "Lump.hpp"
#include "Lump_Header.hpp"

namespace WAD {

[[nodiscard]] std::vector<Lump_Header>
read_all_lumps(const std::vector<uint8_t> &wad_data, const Header &header);

[[nodiscard]] std::vector<Lump>
convert_headers_to_full(const std::vector<uint8_t> &,
                        const std::vector<Lump_Header> &);

} // namespace WAD
