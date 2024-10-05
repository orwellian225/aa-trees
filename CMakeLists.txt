cmake_minimum_required(VERSION 3.16)

project(AA-Trees DESCRIPTION "COMS4032A AA Assignment 2: Binary Search Trees" LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED On)
set(CMAKE_C_EXTENSIONS Off)

add_executable(bst-test
	src/bst-test.c src/bs-trees.c
)
target_link_libraries(bst-test m)
target_include_directories(bst-test PUBLIC include)
target_link_directories(bst-test PRIVATE src)

add_executable(ost-test
	src/os-test.c src/os-trees.c
)
target_link_libraries(ost-test m)
target_include_directories(ost-test PUBLIC include)
target_link_directories(ost-test PRIVATE src)

add_executable(random-insert
	src/random-insert.c src/bs-trees.c src/os-trees.c
)
target_link_libraries(random-insert m)
target_include_directories(random-insert PUBLIC include)
target_link_directories(random-insert PRIVATE src)

add_executable(descending-insert
	src/descending-insert.c src/bs-trees.c src/os-trees.c
)
target_link_libraries(descending-insert m)
target_include_directories(descending-insert PUBLIC include)
target_link_directories(descending-insert PRIVATE src)

add_executable(order-statistics
	src/os-algs.c src/os-trees.c
)
target_link_libraries(order-statistics m)
target_include_directories(order-statistics PUBLIC include)
target_link_directories(order-statistics PRIVATE src)
