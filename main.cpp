#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
using ms = std::chrono::milliseconds;

struct A {
    int x = 0;
    int y = 1;
} a;

void fx() {
    for (int i = 0; i < 1'000'000'000; i++)
        a.x++;
}

void fy() {
    int sum = 0;
    for (int i = 0; i < 1'000'000'000; i++)
        sum += a.y;
}

int main() {
    for (int i = 0; i < 20; i++) {
        auto t1 = steady_clock::now();
        // fx();
        // fy();

        std::thread tx(fx);
        std::thread ty(fy);

        tx.join();
        ty.join();
        auto t2 = steady_clock::now();

        std::cout << "Time: " << duration_cast<ms>(t2 - t1).count() << " ms\n";
    }
}