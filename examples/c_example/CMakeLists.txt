project(c_example)

set(SRC
    main.c
)

add_executable(c_example ${SRC})

include_directories(../../include)

target_link_libraries(c_example bitbang)
