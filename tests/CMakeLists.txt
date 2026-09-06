# Core regression tests deliberately avoid the shared library's SDL runtime
# dependency so they can run headlessly without staging native redist binaries.
enable_language(C)
add_library(header_c_check OBJECT header.c)
add_library(header_cpp_check OBJECT header.cpp)
target_include_directories(header_c_check PRIVATE ../src)
target_include_directories(header_cpp_check PRIVATE ../src)
set_target_properties(header_c_check PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)

add_executable(wrapper_regression_test
    wrapper_regression.cpp
    ${IMGUI_SOURCES}
    ../src/imgui_sharp.cpp
    ../src/imgui_sharp_layout_check.cpp
)
target_include_directories(wrapper_regression_test PRIVATE ../src ${IMGUI_DIR})
target_compile_definitions(wrapper_regression_test PRIVATE
    IMGUI_SHARP_EXPORT IMGUI_DISABLE_OBSOLETE_FUNCTIONS)
add_test(NAME wrapper_regression COMMAND wrapper_regression_test)

# Compile against real upstream backend signatures, replacing their implementations
# with recording stubs. SDL's target supplies headers only to this object library;
# the executable consumes its objects without linking SDL or requiring a GPU.
add_library(backend_forwarding_objects OBJECT
    backend_forwarding.cpp ../src/imgui_sharp_backend.cpp)
target_include_directories(backend_forwarding_objects PRIVATE
    ../src ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_compile_definitions(backend_forwarding_objects PRIVATE
    IMGUI_SHARP_EXPORT IMGUI_DISABLE_OBSOLETE_FUNCTIONS)
target_link_libraries(backend_forwarding_objects PRIVATE SDL3::SDL3)
add_executable(backend_forwarding_test $<TARGET_OBJECTS:backend_forwarding_objects>)
add_test(NAME backend_forwarding COMMAND backend_forwarding_test)
