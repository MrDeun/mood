# mood

A Doom source port built for the funnies.

## Status

Early development. WAD parsing is functional and a palette viewer renders
PLAYPAL data via SFML.

## Features

- **WAD parsing** — reads IWAD/PWAD headers, directories, and lump data
- **Palette viewer** — interactive SFML window that displays colour palettes
  from a WAD's `PLAYPAL` lump, navigable with Up/Down arrows
- **CLI** — specify a WAD file with `-f` / `--file`

## Build

Requirements: C++17 compiler, [Xmake](https://xmake.io).

```bash
xmake
```

## Usage

```bash
./build/<os>/<arch>/<build_type>/mood -h

Mood - Doom source port for the funnies


./mood [OPTIONS]


OPTIONS:
  -h,     --help              Print this help message and exit
  -f,     --file TEXT         Assign wad file to load

```

## Project structure

- `src/` — source code
- `src/include/WAD.hpp` — umbrella header for the WAD library
- `src/include/WAD/` — WAD library headers
  - `Header.hpp` — WAD header struct and parsing
  - `Lump.hpp` — lump container (header + binary data)
  - `Lump_Header.hpp` — lump directory entry struct
  - `LumpTypes.hpp` — typed lump extractors (palettes, etc.)
  - `WADFile.hpp` — main WAD file class
  - `utils.hpp` — helpers for reading lumps
- `src/lib/` — WAD library implementations
- `src/main.cpp` — entry point, CLI, and palette viewer
- `src/vendors/` — vendored header-only dependencies (CLI11, nlohmann/json)
- `resources/fonts/` — fonts used by the renderer
- `wads/` — bundled test WAD files

## Dependencies

- [fmt](https://fmt.dev) — fetched automatically by Xmake
- [SFML](https://sfml-dev.org) — fetched automatically by Xmake
- CLI11 (vendored)
- nlohmann/json (vendored)

## Roadmap (likely)

- [x] WAD parsing
- [ ] Create method for collecting all WAD's maps 
- [x] Palette extraction and rendering
- [ ] Map/level loading
- [ ] Full rendering (software or GPU)
- [ ] Input handling
- [ ] Audio
- [ ] Game logic
- [ ] Full source port features

## License

See [LICENSE](LICENSE) (if present).
