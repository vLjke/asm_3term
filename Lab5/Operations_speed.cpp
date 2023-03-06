#include <iostream>
#include <xmmintrin.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

float a = 10e-43, b = 5e-43, c;

int main()
{
    for (int i = 0; i < 20; ++i) {
        // Отключаем денормализованные числа
        _mm_setcsr(_mm_getcsr() | 0x8040);
        auto begin = high_resolution_clock::now();
        asm
        (
            "movl   $200000, %eax\n"
            "movl   $0, %ebx\n"
            "movss  a(%rip), %xmm0\n"
            "movss  b(%rip), %xmm1\n"
            "Cycle:\n"                  //  В цикле 200 000 раз применяем операцию
            "subss  %xmm1, %xmm0\n"
            "addl   $1, %ebx\n"
            "cmpl   %eax, %ebx\n"
            "jne    Cycle\n"
            "movss  %xmm0, c(%rip)\n"
                );
        auto end = high_resolution_clock::now();
        // Запоминаем время и результат
        auto dur1 = duration_cast<microseconds>(end - begin);
        auto sum1 = c;

        // Включаем денормализованные числа и делаем то же самое
        _mm_setcsr(_mm_getcsr() & ~0x8040);
        begin = high_resolution_clock::now();
        asm
        (   
            "movl   $200000, %eax\n"
            "movl   $0, %ebx\n"
            "movss  a(%rip), %xmm0\n"
            "movss  b(%rip), %xmm1\n"
            "Cycle1:\n"
            "subss  %xmm1, %xmm0\n"
            "addl   $1, %ebx\n"
            "cmpl   %eax, %ebx\n"
            "jne    Cycle1\n"
            "movss  %xmm0, c(%rip)\n"   
                );

        end = high_resolution_clock::now();
        auto dur2 = duration_cast<microseconds>(end - begin);
        auto sum2 = c;
        // Выводим результат операций и время выполнения
        cout << "denormals are zero (" << sum1 << "): " << dur1.count() << " us" 
        << "; denormals are not zero(" << sum2 << "): " << dur2.count() << " us" << endl;
    }
    return 0;
}
