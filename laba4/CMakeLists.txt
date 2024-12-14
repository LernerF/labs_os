cmake_minimum_required(VERSION 3.10)
project(DynamicLibExample)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 11)

# Подключение FetchContent для Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(googletest)

# Создание библиотек
add_library(rectangle SHARED src/rectangle.cpp)
add_library(triangle SHARED src/triangle.cpp)

# Указываем пути к заголовочным файлам
target_include_directories(rectangle PUBLIC include)
target_include_directories(triangle PUBLIC include)

# Создание исполняемых файлов
add_executable(main main.cpp)
add_executable(main_dynamic main_dynamic.cpp)

# Линкуем main с библиотекой rectangle
target_link_libraries(main PRIVATE rectangle)

# Линкуем Google Test с тестами
add_executable(test_functions tests/test_functions.cpp)
target_link_libraries(test_functions gtest gtest_main pthread)

# Добавление тестов
enable_testing()
add_test(NAME FunctionsTest COMMAND test_functions)