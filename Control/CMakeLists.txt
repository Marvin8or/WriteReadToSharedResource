project(Control)
file(GLOB Control_src "*.h" "*.cpp")
add_library(Control ${Control_src})
target_include_directories(Control PUBLIC "{PROJECT_BINARY_DIR}/Utils")

target_link_libraries(Control PUBLIC Utils)
