#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <xmmintrin.h>

using namespace std::chrono;

int main() {
    // Отключаем денормализованные числа
    _mm_setcsr(_mm_getcsr() & ~0x8040);
    std::ofstream pi;
    pi.open("Pi_accuracy2_optimized.txt");
    std::ofstream time;
    time.open("Time2_optimized.txt");
    size_t PRECISION = 15;
    // Двa произведения вместо одного
    double mul1 = 1;
    double mul2 = 1;
    // Начало отсчёта
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1e6 / 2; i += 1) {
        mul1 *= (2 * (i + 1) / static_cast<double>(2 * (i + 1) - 1));
        mul2 *= (2 * (i + 1) / static_cast<double>(2 * (i + 1) + 1));
        pi << std::setprecision(PRECISION) << fabs(2 * mul1 * mul2 - M_PI) << std::endl;
        // Запоминаем время на итерации
        time << duration_cast<microseconds>(high_resolution_clock::now() - start).count() << std::endl;
    }
    return 0;
}