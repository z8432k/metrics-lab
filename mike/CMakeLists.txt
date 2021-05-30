include_directories(".")

add_library(reg OBJECT reg.cc)

add_executable(register main.cc)
target_link_libraries(register reg)
