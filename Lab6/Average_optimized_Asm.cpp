#include <iostream>
#include <chrono>
#include <typeinfo>
#include <ctime>

using namespace std::chrono;

// Инициализация статического массива
const int N = 16000000;
double massive[N];
// Переменная, где потом будет результат
double aver = 0;

int main() {
// Цикл для измерения времени несколько раз
    for (int i = 0; i < 20; ++i) {
        // Генерация случайных чисел от 0 до 10
        srand(time(NULL));
        for (int i = 0; i < N; ++i) {
            massive[i] = rand() % 10;
        }
        // Старт замера времени и вычисления среднего арифметического
        auto start = high_resolution_clock::now();
        asm
        (
            "leaq   massive(%rip), %r11\n" // Адрес нулевого элемента изначально кладём в %r11
            "movq   $15999998, %rbx\n" 
            "leaq   (%r11, %rbx, 8), %r12\n" // Адрес предпоследнего элемента (для выхода из цикла)
            "movq   $2, %rbx\n"
            "movupd massive(%rip), %xmm0\n" // Перед циклом кладём первые два double'a в %xmm0, 
                                            //в %xmm0 будут копиться две суммы
            "Cycle:\n"
            "addpd  (%r11, %rbx, 8), %xmm0\n" // Складываем по два элемента за одну операцию
            "leaq   (%r11, %rbx, 8), %r11\n" // Теперь %r11 указывает на элемент через один 
            "cmp    %r11, %r12\n"
            "jne    Cycle\n"
            "movhpd %xmm0, aver(%rip)\n" // Отделяем первую сумму
            "movsd  aver(%rip), %xmm1\n"  
            "addsd  %xmm0, %xmm1\n" // Складываем обе суммы
            "movsd  %xmm1, aver(%rip)\n" 
        );
        aver /= N;
        // Конец замера времени
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Time consumed: " << duration.count() << " us"<< std::endl;
    }
    return 0;
}