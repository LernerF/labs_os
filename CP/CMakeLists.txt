cmake_minimum_required(VERSION 3.10)
project(MemoryAllocator)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

# Подключение заголовочных файлов
include_directories(include)

# Подключение Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Основной проект
add_executable(main
    src/main.cpp
    src/allocator_mckusick.cpp
    src/allocator_pow2.cpp
)

target_link_libraries(main pthread)

# Тесты
add_executable(benchmark_allocators
    tests/benchmark_allocators.cpp
    src/allocator_mckusick.cpp
    src/allocator_pow2.cpp
)
target_link_libraries(benchmark_allocators gtest gtest_main pthread)

add_test(NAME AllocatorBenchmark COMMAND benchmark_allocators)