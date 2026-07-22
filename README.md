# mood

A Doom source port built for the funnies.

## Status

Early development. Currently only parses WAD files and outputs lump metadata as JSON.

## Features

- **WAD parsing** — reads IWAD/PWAD headers, directories, and lump metadata
- **JSON output** — dumps WAD structure (header + lump table) to stdout
- **CLI** — specify a WAD file with `-f` / `--file`

## Build

Requirements: C++17 compiler, [Xmake](https://xmake.io).

```bash
xmake
```

## Usage

```bash
xmake run mood -f <path-to-WAD>
```

## Project structure

- `src/` — source code
- `src/include/WAD.hpp` — WAD parser interface
- `src/lib/WAD.cpp` — WAD parser implementation
- `src/main.cpp` — entry point and CLI
- `src/vendors/` — vendored header-only dependencies (CLI11, nlohmann/json)

## Dependencies

- [fmt](https://fmt.dev) — fetched automatically by Xmake
- CLI11 (vendored)
- nlohmann/json (vendored)

## Roadmap (likely)

- [ ] Map/level loading
- [ ] Rendering (software or GPU)
- [ ] Input handling
- [ ] Audio
- [ ] Game logic
- [ ] Full source port features

## License

See [LICENSE](LICENSE) (if present).
