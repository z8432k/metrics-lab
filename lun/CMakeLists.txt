add_library(theatre OBJECT theatre.cc)

add_executable(lun Source.cc)
target_link_libraries(lun theatre)
