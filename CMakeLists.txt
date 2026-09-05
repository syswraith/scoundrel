cmake_minimum_required(VERSION 3.20)
project(MyCppProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ftxui REQUIRED)

include_directories(include)

file(GLOB_RECURSE SRC_FILES "src/main.cpp" "src/room.cpp" "src/player.cpp" "src/deck.cpp")

add_executable(main ${SRC_FILES})

target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(main PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -fexec-charset=utf-8
    )
endif()

find_program(VALGRIND_PROGRAM valgrind)
if(VALGRIND_PROGRAM)
    enable_testing()
    add_test(
        NAME ValgrindMemCheck
        COMMAND ${VALGRIND_PROGRAM}
            --leak-check=full
            --show-leak-kinds=all
            --track-origins=yes
            --errors-for-leak-kinds=all
            --error-exitcode=1
            $<TARGET_FILE:main>
    )
else()
    message(WARNING "Valgrind not found. Testing will be unavailable.")
endif()
