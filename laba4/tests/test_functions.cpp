#include <gtest/gtest.h>
#include <dlfcn.h>
#include <stdexcept>
#include <string>

void* load_library(const std::string& library_path, float (**Square)(float, float), char* (**translation)(long)) {
    void* handle = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle) {
        const char* err = dlerror();
        throw std::runtime_error(err ? err : "Failed to open library and dlerror() returned NULL");
    }

    // Сбрасываем ошибку перед следующим вызовом dlsym
    dlerror();
    *Square = (float (*)(float, float))dlsym(handle, "Square");
    const char* squareErr = dlerror();
    if (squareErr) {
        dlclose(handle);
        throw std::runtime_error(squareErr);
    }

    dlerror();
    *translation = (char* (*)(long))dlsym(handle, "translation");
    const char* translationErr = dlerror();
    if (translationErr) {
        dlclose(handle);
        throw std::runtime_error(translationErr);
    }

    return handle;
}

TEST(RectangleLibTest, CalculateRectangleArea) {
    float (*Square)(float, float);
    char* (*translation)(long);

    void* handle = nullptr;
    try {
        handle = load_library("../build/librectangle.so", &Square, &translation);
        ASSERT_NE(Square, nullptr) << "Square function not loaded";
        ASSERT_NE(translation, nullptr) << "translation function not loaded";

        // Проверяем площадь
        EXPECT_FLOAT_EQ(Square(5.0, 10.0), 50.0);
        EXPECT_FLOAT_EQ(Square(0.0, 10.0), 0.0);
    } catch (const std::exception& e) {
        FAIL() << "Exception caught: " << e.what();
    }

    if (handle) {
        dlclose(handle);
    }
}

TEST(RectangleLibTest, ConvertToBinary) {
    float (*Square)(float, float);
    char* (*translation)(long);

    void* handle = nullptr;
    try {
        handle = load_library("../build/librectangle.so", &Square, &translation);
        ASSERT_NE(Square, nullptr) << "Square function not loaded";
        ASSERT_NE(translation, nullptr) << "translation function not loaded";

        // Проверяем перевод числа 10
        char* result = translation(10);
        ASSERT_NE(result, nullptr) << "translation(10) returned nullptr";
        EXPECT_STREQ(result, "1010");

        // Проверяем перевод числа 0
        result = translation(0);
        ASSERT_NE(result, nullptr) << "translation(0) returned nullptr";
        EXPECT_STREQ(result, "0");
    } catch (const std::exception& e) {
        FAIL() << "Exception caught: " << e.what();
    }

    if (handle) {
        dlclose(handle);
    }
}
