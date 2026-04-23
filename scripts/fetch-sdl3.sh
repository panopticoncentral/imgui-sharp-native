#!/usr/bin/env bash
# Download and extract the SDL3 macOS DMG framework. Used by CI (and
# optionally local builds) to acquire libSDL3.dylib for linking. Verifies
# SHA256 against scripts/sdl3-versions.json.
#
# Outputs SDL3_ROOT=<path> on stdout and, when running in GitHub Actions,
# appends it to $GITHUB_ENV. SDL3_ROOT points at a directory containing
# SDL3Config.cmake so find_package(SDL3 CONFIG) works.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEST_DIR="${1:-$SCRIPT_DIR/../sdl3}"
mkdir -p "$DEST_DIR"

VERSIONS="$SCRIPT_DIR/sdl3-versions.json"
URL=$(python3 -c "import json; print(json.load(open('$VERSIONS'))['macos']['url'])")
EXPECTED_SHA=$(python3 -c "import json; print(json.load(open('$VERSIONS'))['macos']['sha256'])")
SDL3_VERSION=$(python3 -c "import json; print(json.load(open('$VERSIONS'))['sdl3_version'])")

DMG_PATH="$DEST_DIR/SDL3-$SDL3_VERSION.dmg"
STAGE_DIR="$DEST_DIR/SDL3-$SDL3_VERSION"

if [ ! -f "$DMG_PATH" ]; then
    echo "Downloading $URL"
    curl -L --fail -o "$DMG_PATH" "$URL"
fi

ACTUAL_SHA=$(shasum -a 256 "$DMG_PATH" | awk '{print $1}')
if [ "$ACTUAL_SHA" != "$EXPECTED_SHA" ]; then
    echo "SHA256 mismatch for SDL3 DMG" >&2
    echo "  expected: $EXPECTED_SHA" >&2
    echo "  actual:   $ACTUAL_SHA" >&2
    exit 1
fi
echo "SHA256 OK: $ACTUAL_SHA"

if [ ! -d "$STAGE_DIR" ]; then
    MOUNT="/tmp/imgui-sharp-sdl3-mount-$$"
    mkdir -p "$STAGE_DIR/lib/cmake/SDL3"
    hdiutil detach "$MOUNT" -force 2>/dev/null || true
    hdiutil attach "$DMG_PATH" -mountpoint "$MOUNT" -nobrowse
    trap 'hdiutil detach "$MOUNT" -force 2>/dev/null || true' EXIT

    # The DMG contains SDL3.xcframework/macos-arm64_x86_64/SDL3.framework
    # with the universal dylib inside Versions/A/SDL3. We copy headers and
    # synthesize a dylib + minimal CMake config so find_package(SDL3 CONFIG)
    # can locate it. Headers go under include/SDL3/ to match the VC zip
    # layout so consumers can #include <SDL3/SDL.h>.
    FW="$MOUNT/SDL3.xcframework/macos-arm64_x86_64/SDL3.framework"
    mkdir -p "$STAGE_DIR/include/SDL3"
    cp -R "$FW/Versions/A/Headers/"* "$STAGE_DIR/include/SDL3/"
    cp "$FW/Versions/A/SDL3" "$STAGE_DIR/lib/libSDL3.dylib"
    install_name_tool -id "@rpath/libSDL3.0.dylib" "$STAGE_DIR/lib/libSDL3.dylib" 2>/dev/null || true

    # Emit a minimal SDL3Config.cmake that exposes SDL3::SDL3 as an imported
    # shared library — matching what the VC zip's config does.
    cat > "$STAGE_DIR/lib/cmake/SDL3/SDL3Config.cmake" <<'EOF'
# Synthesized by scripts/fetch-sdl3.sh for the macOS DMG payload.
get_filename_component(_sdl3_root "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)

add_library(SDL3::SDL3-shared SHARED IMPORTED)
set_target_properties(SDL3::SDL3-shared PROPERTIES
    IMPORTED_LOCATION "${_sdl3_root}/lib/libSDL3.dylib"
    INTERFACE_INCLUDE_DIRECTORIES "${_sdl3_root}/include"
)

add_library(SDL3::SDL3 INTERFACE IMPORTED)
set_target_properties(SDL3::SDL3 PROPERTIES
    INTERFACE_LINK_LIBRARIES SDL3::SDL3-shared
)

set(SDL3_FOUND TRUE)
EOF
fi

SDL3_ROOT="$(cd "$STAGE_DIR" && pwd)"
echo "SDL3_ROOT=$SDL3_ROOT"

if [ -n "${GITHUB_ENV:-}" ]; then
    echo "SDL3_ROOT=$SDL3_ROOT" >> "$GITHUB_ENV"
fi
