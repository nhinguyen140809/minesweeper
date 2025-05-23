# Minesweeper Game (SFML 3.0)

A simple implementation of the classic **Minesweeper** game using **SFML 3.0**, with a responsive GUI, mouse interaction, and support for multiple platforms (Windows, macOS, Linux).

## Features

- Classic Minesweeper gameplay
- Left-click to reveal, right-click to flag
- Multiple game modes (Easy, Medium, Hard)
- Ripple visual effect on win or loss
- Static linking with SFML 3.0 (no external DLLs needed)
- Cross-platform support

## GitHub Actions (CI)
This project includes a GitHub Actions workflow to automatically build the game on:
- Ubuntu
- macOS
Download from [GitHub Actions → Latest run → Artifacts] (https://github.com/nhinguyen140809/minesweeper/actions)

Windows is excluded due to static linking limitations in GitHub-hosted runners.

## Build Instructions

### Prerequisites

- CMake 3.15 or newer
- C++17 compiler
- SFML 3.0 (built from source with static libraries)

---

### Build on Windows

You need to build and install SFML 3.0 from source with static linking enabled. 

Follow the official SFML build-from-source instructions here: https://www.sfml-dev.org/tutorials/3.0/getting-started/build-from-source/

Open a terminal (e.g., PowerShell or Command Prompt), navigate to the project root directory (where `CMakeLists.txt` is located), then run:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DSFML_DIR="<path_to_SFML_install>/lib/cmake/SFML"
cmake --build build --config Release
```

---
### Build on MacOS

Make sure you have Homebrew installed, then run:
```bash
brew install cmake

git clone --branch 3.0.x https://github.com/SFML/SFML.git
cmake -S SFML -B SFML/build -DSFML_BUILD_EXAMPLES=OFF -DSFML_STATIC_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=SFML/install
cmake --build SFML/build --config Release --target install

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DSFML_DIR=SFML/install/lib/cmake/SFML
cmake --build build --config Release
```

---
### Build on Linux

Run these commands for install the necessary dependencies and tools, clone and build SFML 3.0 from source, and finally build your game using the installed SFML:

```bash
sudo apt update && sudo apt install -y cmake g++ \
    libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev \
    libgl1-mesa-dev libudev-dev libfreetype6-dev libopenal-dev \
    libflac-dev libvorbis-dev

git clone --branch 3.0.x https://github.com/SFML/SFML.git
cmake -S SFML -B SFML/build -DSFML_BUILD_EXAMPLES=OFF -DSFML_STATIC_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=SFML/install
cmake --build SFML/build --config Release --target install

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DSFML_DIR=SFML/install/lib/cmake/SFML
cmake --build build --config Release
```

## Acknowledgements

- **Font**: This project uses a font obtained from [Google Fonts](https://fonts.google.com/).
- **Icons**: Icons used in the game are sourced from [Flaticon](https://www.flaticon.com/).

