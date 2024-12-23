# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MatrixFilterProject)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем пути к заголовочным файлам
include_directories(include)

# Исходники для основного приложения
set(SRC_FILES
    src/main.cpp
    src/matrix_utils.cpp
    src/median_filter.cpp
)

# Создание исполняемого файла для основного приложения
add_executable(matrix_filter ${SRC_FILES})
target_compile_options(matrix_filter PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(matrix_filter pthread)

# Подключение Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Исходники для тестов
set(TEST_FILES
    tests/test_main.cpp
    tests/test_matrix.cpp
    tests/test_median.cpp
)

# Создание исполняемого файла для тестов
add_executable(test_program ${TEST_FILES} src/matrix_utils.cpp src/median_filter.cpp)
target_link_libraries(test_program GTest::GTest GTest::Main pthread)

# Добавление тестов
add_test(NAME RunTests COMMAND test_program)

# Установка политики CMP0012 и CMP0003 для устранения предупреждений
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0012 NEW) # Распознавание ON как булевое значение
    cmake_policy(SET CMP0003 NEW) # Логика поиска библиотек
endif()