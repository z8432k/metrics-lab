add_library(foto OBJECT foto.cc)

add_executable(fotobase main.cc)
target_link_libraries(fotobase foto)
