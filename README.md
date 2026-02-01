# Dune-Rendering

[🇯🇵 日本語版](README_ja.md)

## Overview

Dune-Rendering is an interactive visualization project built with openFrameworks. It creates stunning desert and sand dune renders with real-time interactivity.

## Features

- Real-time 3D rendering of desert landscapes
- Interactive camera controls
- Custom GLSL shaders for advanced visual effects
- OpenGL-based graphics with openFrameworks framework

## Project Structure

```
src/
  ├── main.cpp          # Entry point
  ├── ofApp.cpp         # Application implementation
  └── ofApp.h           # Application header

bin/
  └── data/
      ├── shader.vert   # Vertex shader
      └── shader.frag   # Fragment shader

config.make            # Build configuration
addons.make            # OpenFrameworks addons
```

## Requirements

- Visual Studio 2022 or later
- openFrameworks v0.12.1
- Windows x64 platform

## Building

1. Open `Dune_Rendering.sln` in Visual Studio
2. Build the solution (Debug or Release configuration)
3. Run the executable from `bin/` directory

## Shaders

The project uses custom GLSL shaders located in `bin/data/`:
- `shader.vert` - Vertex shader for geometry transformation
- `shader.frag` - Fragment shader for pixel-level effects

## License

See [LICENSE](LICENSE) file for details.

## Author

Created as an openFrameworks rendering experiment.