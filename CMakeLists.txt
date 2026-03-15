cmake_minimum_required(VERSION 3.20)
project(imgui_sharp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Paths to sibling repos
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/../imgui")
set(SDL_DIR "${CMAKE_SOURCE_DIR}/../SDL")

# SDL3 - find via cmake package or fall back to local build
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
    # Try local SDL build
    if(EXISTS "${SDL_DIR}/build")
        list(APPEND CMAKE_PREFIX_PATH "${SDL_DIR}/build")
        find_package(SDL3 REQUIRED)
    else()
        message(FATAL_ERROR "SDL3 not found. Build SDL3 first: cd ../SDL && cmake -B build && cmake --build build")
    endif()
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
