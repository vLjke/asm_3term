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
    pi.open("Pi_accuracy1_optimized.txt");
    std::ofstream time;
    time.open("Time1_optimized.txt");
    size_t PRECISION = 15;
    // Две суммы вместо одной
    double sum1 = 0;
    double sum2 = 0;
    // Начало отсчёта
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1e6; i += 2) {
        sum1 += (1 / static_cast<double>(2 * (i + 1) - 1));
        sum2 -= (1 / static_cast<double>(2 * (i + 1) + 1));
        pi << std::setprecision(PRECISION) << fabs(4 * (sum1 + sum2) - M_PI) << std::endl;
        // Запоминаем время на итерации
        time << duration_cast<microseconds>(high_resolution_clock::now() - start).count() << std::endl;
    }
    return 0;
}