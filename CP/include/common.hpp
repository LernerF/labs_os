#ifndef COMMON_HPP
#define COMMON_HPP

#include <chrono>

class Timer {
public:
    void start() { start_time = std::chrono::high_resolution_clock::now(); }
    void stop() { end_time = std::chrono::high_resolution_clock::now(); }
    double elapsed_ns() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time, end_time;
};

#endif // COMMON_HPP