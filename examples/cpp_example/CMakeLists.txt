project(cpp_example)

set(SRC
    main.cpp
)

add_executable(cpp_example ${SRC})

include_directories(../../include)

target_link_libraries(cpp_example bitbang)
