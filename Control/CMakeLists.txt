project(Control)
file(GLOB Control_src "*.h" "*.cpp")
add_library(Control ${Control_src})