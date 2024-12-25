#include "allocator_mckusick.hpp"
#include "allocator_pow2.hpp"
#include <gtest/gtest.h>

TEST(AllocatorMcKusick, AllocateDeallocate) {
    AllocatorMcKusick mckusick(1 << 20);
    void* block1 = mckusick.allocate(64);
    EXPECT_NE(block1, nullptr);

    mckusick.deallocate(block1);
    SUCCEED(); 
}

TEST(AllocatorPow2, AllocateDeallocate) {
    AllocatorPow2 pow2(1 << 20);
    void* block1 = pow2.allocate(64);
    EXPECT_NE(block1, nullptr);

    pow2.deallocate(block1);
    SUCCEED();
}

TEST(AllocatorMcKusick, MultipleAllocations) {
    AllocatorMcKusick mckusick(1 << 20);
    std::vector<void*> blocks;
    for (int i = 0; i < 100; ++i) {
        blocks.push_back(mckusick.allocate(64));
    }
    for (auto block : blocks) {
        mckusick.deallocate(block);
    }
    SUCCEED(); 
}

TEST(AllocatorPow2, MultipleAllocations) {
    AllocatorPow2 pow2(1 << 20);
    std::vector<void*> blocks;
    for (int i = 0; i < 100; ++i) {
        blocks.push_back(pow2.allocate(64));
    }
    for (auto block : blocks) {
        pow2.deallocate(block);
    }
    SUCCEED(); 
}