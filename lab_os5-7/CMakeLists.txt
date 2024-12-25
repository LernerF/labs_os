cmake_minimum_required(VERSION 3.14)
project(DistributedSystem LANGUAGES CXX)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для тестов (CTest + Google Test)
enable_testing()

# -----------------------------------------
# 1. Подключаем FetchContent для зависимостей
# -----------------------------------------
include(FetchContent)

# =========================================
# ЗАГРУЗКА И НАСТРОЙКА ZeroMQ
# =========================================
FetchContent_Declare(
    zmq
    GIT_REPOSITORY https://github.com/zeromq/libzmq.git
    GIT_TAG        v4.3.4
)

# Отключаем любые тесты и документацию ZeroMQ, чтобы лишнего не тянуть
set(ENABLE_TESTS OFF CACHE BOOL "Disable ZeroMQ tests" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "Disable ZeroMQ tests" FORCE)
set(ENABLE_CPACK OFF CACHE BOOL "Disable ZeroMQ CPack" FORCE)
set(ENABLE_DOCS OFF CACHE BOOL "Disable ZeroMQ documentation" FORCE)
set(ZMQ_BUILD_TESTS OFF CACHE BOOL "Disable ZeroMQ tests" FORCE)
set(ENABLE_DRAFTS OFF CACHE BOOL "Disable ZeroMQ drafts" FORCE)

# Скачиваем и собираем libzmq
FetchContent_MakeAvailable(zmq)

# =========================================
# ЗАГРУЗКА Google Test
# =========================================
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1
)

# Скачиваем и собираем Google Test
FetchContent_MakeAvailable(googletest)

# -----------------------------------------
# 2. Создаём статическую библиотеку CoreLib
#    (только логика, без main())
# -----------------------------------------
add_library(CoreLib STATIC
    src/NodeManager.cpp
    src/Messaging.cpp
    src/ComputeNode.cpp  # Если у вас есть ComputeNode.cpp (без main)
)
target_include_directories(CoreLib PUBLIC include)
target_link_libraries(CoreLib PRIVATE zmq)

# -----------------------------------------
# 3. Основной исполняемый файл DistributedSystem
#    (консольный интерфейс для NodeManager)
# -----------------------------------------
add_executable(DistributedSystem
    src/main.cpp
)
target_include_directories(DistributedSystem PUBLIC include)
target_link_libraries(DistributedSystem PRIVATE CoreLib)

# -----------------------------------------
# 4. Исполняемый файл для процесса вычислительного узла
#    (ComputeNodeProcess), где есть свой main()
# -----------------------------------------
add_executable(ComputeNodeProcess
    src/ComputeNodeProcess.cpp
)
target_link_libraries(ComputeNodeProcess PRIVATE zmq)

# -----------------------------------------
# 5. Тесты: Собираем в один исполняемый файл
#    DistributedSystemTests (GTest + CoreLib)
# -----------------------------------------
add_executable(DistributedSystemTests
    tests/NodeManagerTests.cpp
    tests/MessagingTests.cpp
)
target_include_directories(DistributedSystemTests PUBLIC include)
target_link_libraries(DistributedSystemTests PRIVATE 
    CoreLib        # логика (NodeManager, Messaging и т.д.)
    gtest 
    gtest_main
)

# Регистрируем тест, чтобы вызывался при "ctest"
add_test(NAME DistributedSystemTests COMMAND DistributedSystemTests --output-on-failure)