# VLC Smart Shuffle Plugin

A portable C plugin for VLC Media Player that implements a "Permutation Shuffle." 

Unlike native VLC shuffle (which is random and can repeat songs), Smart Shuffle ensures every item in the playlist is played exactly once before the list is reshuffled for the next cycle.

## Features
- **Permutation Logic:** Uses Fisher-Yates shuffle to ensure no repeats until the cycle ends.
- **Seamless Integration:** Works as a headless interface module.
- **Custom Hotkey:** Toggleable via a user-definable hotkey (Default: `Ctrl+S`).

## 🛠 Build Instructions

### Option A: Automated Build (Recommended)
This repository is configured with **GitHub Actions**. Every push to `main` or every new `Release` will automatically trigger a build process that compiles the plugin for Windows and Linux. You can simply download the `.dll` or `.so` from the **Releases** tab.

### Option B: Build with Docker (Local)
To avoid toolchain conflicts on Windows, use a Docker container with the VLC build environment:

```bash
# 1. Pull the VLC build image
docker pull videolan/vlc-build

# 2. Build the plugin
docker run --rm -v $(pwd):/src -w /src videolan/vlc-build \
    bash -c "mkdir build && cd build && cmake .. && make"
```

### Option C: Manual Build (Linux/MSYS2)
**Prerequisites:** `libvlc-dev`, `cmake`, `gcc`.

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## 📦 Installation

1. Copy the resulting `smart_shuffle.dll` (Windows) or `smart_shuffle.so` (Linux) to:
   `VLC_INSTALL_DIR/plugins/interface/`
2. Restart VLC.
3. Open **Tools $\rightarrow$ Preferences $\rightarrow$ All $\rightarrow$ Interface $\rightarrow$ SmartShuffle**.
4. Assign your preferred hotkey to `key-smart-shuffle` (e.g., `Ctrl+S`).
5. Save and restart VLC.

## 🚀 Usage
1. Load a playlist.
2. Press your assigned hotkey.
3. The plugin will disable native shuffle and begin the Smart Shuffle permutation.
