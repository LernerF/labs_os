#include "NodeManager.h"
#include <gtest/gtest.h>

// Тест на создание узла в тестовом режиме
TEST(NodeManagerTests, CreateSingleNode) {
    NodeManager manager(true);  // true -> тестовый режим
    std::string result = manager.createNode(1, -1);
    // Ожидаем, что строка начнётся с "Ok:"
    ASSERT_TRUE(result.rfind("Ok:", 0) == 0)
        << "Failed to create single node: " << result;
}

// Тест на создание дублирующегося узла
TEST(NodeManagerTests, CreateDuplicateNode) {
    NodeManager manager(true); 
    manager.createNode(1, -1);
    std::string result = manager.createNode(1, -1);
    EXPECT_EQ(result, "Error: Already exists");
}

// Тест на то, что родитель не найден
TEST(NodeManagerTests, ParentNotFound) {
    NodeManager manager(true);
    std::string result = manager.createNode(2, 1); // Узел 1 ещё не создан
    EXPECT_EQ(result, "Error: Parent not found");
}

// Тест execCommand
TEST(NodeManagerTests, ExecCommandNotFound) {
    NodeManager manager(true);
    // Узел 10 не существует
    std::string result = manager.execCommand(10, "hello", "ll");
    EXPECT_EQ(result, "Error: Not found");
}

TEST(NodeManagerTests, ExecCommandOk) {
    NodeManager manager(true);
    manager.createNode(100, -1);
    std::string result = manager.execCommand(100, "hello", "ll");
    // "Ok:100: [hello|ll]"
    EXPECT_TRUE(result.find("Ok:100") != std::string::npos);
}