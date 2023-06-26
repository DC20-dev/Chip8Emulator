cmake_minimum_required(VERSION 3.8)

# MAIN EXECUTABLE
project(Chip8Emulator LANGUAGES CXX)

set(PROJ_SRCS include/emulator.h src/emulator.cpp)

add_executable(Chip8Emulator src/main.cpp ${PROJ_SRCS})

set_property(TARGET Chip8Emulator PROPERTY CXX_STANDARD 20)

target_include_directories(Chip8Emulator PUBLIC src include SDL2/include)

target_link_libraries(Chip8Emulator ${PROJECT_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib)


set(SDL2_LIB_DIR ${PROJECT_SOURCE_DIR}/SDL2/lib/x64)

add_custom_command(
    TARGET Chip8Emulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB_DIR}/SDL2.dll $<TARGET_FILE_DIR:Chip8Emulator>
)

set (RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
add_custom_command(
    TARGET Chip8Emulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} $<TARGET_FILE_DIR:Chip8Emulator>/resources
    )

# BUILD TESTS

project(Chip8Tests LANGUAGES CXX)

set(TEST_SRCS tests/main.cpp tests/test_emulator.cpp) 

add_executable(Chip8Tests ${PROJ_SRCS} ${TEST_SRCS})

# exposes test methods and shuts off prints while testing
target_compile_definitions(Chip8Tests PUBLIC EMU_TEST)

set_property(TARGET Chip8Tests PROPERTY CXX_STANDARD 20)

target_include_directories(Chip8Tests PUBLIC include SDL2/include src)

target_link_libraries(Chip8Tests ${PROJECT_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib)
