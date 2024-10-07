cmake_minimum_required(VERSION 3.9)
project(bitbang VERSION 0.1 DESCRIPTION "FT245RL bitbang sample")

set(SRC
    bitbang.c
)

if ( EXAMPLES )
  add_subdirectory(examples)
endif ( EXAMPLES )

include_directories(include)
add_library(bitbang SHARED ${SRC})

target_include_directories(bitbang PUBLIC /usr/include/libftdi1)
target_link_libraries(bitbang PUBLIC ftdi1)

set_target_properties(bitbang PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/bitbang.h
)

install(TARGETS bitbang
    LIBRARY DESTINATION lib/bitbang
    PUBLIC_HEADER DESTINATION include/bitbang
)
