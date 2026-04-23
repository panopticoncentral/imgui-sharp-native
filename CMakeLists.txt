cmake_minimum_required(VERSION 3.20)
project(imgui_sharp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ImGui sources live in a pinned git submodule at third_party/imgui.
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/third_party/imgui")
if(NOT EXISTS "${IMGUI_DIR}/imgui.cpp")
    message(FATAL_ERROR
        "ImGui submodule not found at ${IMGUI_DIR}. "
        "Run: git submodule update --init --recursive")
endif()

# SDL3: locate via find_package. CI passes -DSDL3_ROOT=<path> pointing at an
# extracted SDL3 development package (VC zip on Windows, DMG contents on macOS).
# Local developers can either set SDL3_ROOT or rely on a system-installed SDL3.
if(DEFINED SDL3_ROOT)
    list(PREPEND CMAKE_PREFIX_PATH "${SDL3_ROOT}")
endif()

find_package(SDL3 CONFIG QUIET)
if(NOT SDL3_FOUND)
    message(FATAL_ERROR
        "SDL3 not found. Pass -DSDL3_ROOT=<path-to-SDL3-dev-package> "
        "or install SDL3 so find_package(SDL3 CONFIG) succeeds.")
endif()

# ImGui core sources
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
)

# ImGui SDL3 backend sources
set(IMGUI_BACKEND_SOURCES
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlgpu3.cpp
)

# Our C wrapper sources
set(WRAPPER_SOURCES
    src/imgui_sharp.cpp
    src/imgui_sharp_backend.cpp
)

add_library(imgui_sharp SHARED
    ${IMGUI_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
    ${WRAPPER_SOURCES}
)

target_include_directories(imgui_sharp PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(imgui_sharp PRIVATE SDL3::SDL3)

# Export visibility
target_compile_definitions(imgui_sharp PRIVATE IMGUI_SHARP_EXPORT)

# Hide all symbols by default, only export our C wrapper functions
if(NOT MSVC)
    target_compile_options(imgui_sharp PRIVATE -fvisibility=hidden)
endif()

# On macOS, rewrite the SDL3 dependency to @loader_path so imgui_sharp uses
# the same libSDL3.dylib that the .NET runtime loads (from SdlSharp.Redist),
# avoiding duplicate SDL3 copies in the same process.
if(APPLE)
    set_target_properties(imgui_sharp PROPERTIES
        BUILD_RPATH ""
        INSTALL_RPATH ""
        BUILD_WITH_INSTALL_RPATH ON
    )
    add_custom_command(TARGET imgui_sharp POST_BUILD
        COMMAND install_name_tool -change @rpath/libSDL3.0.dylib @loader_path/libSDL3.dylib $<TARGET_FILE:imgui_sharp>
        COMMENT "Rewriting SDL3 dependency to @loader_path"
    )
endif()

# Install
install(TARGETS imgui_sharp
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
