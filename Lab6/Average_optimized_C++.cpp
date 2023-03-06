#include <iostream>
#include <chrono>
#include <typeinfo>
#include <ctime>

using namespace std::chrono;

const int N = 16000000;
double massive[N] = {0};

double aver = 0;
// Создаём много сумм
double sum1 = 0;
double sum2 = 0;
double sum3 = 0;
double sum4 = 0;
double sum5 = 0;
double sum6 = 0;
double sum7 = 0;
double sum8 = 0;
double sum9 = 0;
double sum10 = 0;

int main() {
    for (int i = 0; i < 20; ++i) {
        srand(time(NULL));
        for (int i = 0; i < N; ++i) {
            massive[i] = rand() % 10;
        }
        // Засекаем время начала 
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i += 6) {
            // Меняем количество сумм, участвующих в вычислении
            /*if (i + 9 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
                sum4 += massive[i + 3];
                sum5 += massive[i + 4];
                sum6 += massive[i + 5];
                sum7 += massive[i + 6];
                sum8 += massive[i + 7];
                sum9 += massive[i + 8];
                sum10 += massive[i + 9];
            }
            if (i + 8 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
                sum4 += massive[i + 3];
                sum5 += massive[i + 4];
                sum6 += massive[i + 5];
                sum7 += massive[i + 6];
                sum8 += massive[i + 7];
                sum9 += massive[i + 8];
            }
            if (i + 7 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
                sum4 += massive[i + 3];
                sum5 += massive[i + 4];
                sum6 += massive[i + 5];
                sum7 += massive[i + 6];
                sum8 += massive[i + 7];
            }
            else if (i + 6 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
                sum4 += massive[i + 3];
                sum5 += massive[i + 4];
                sum6 += massive[i + 5];
                sum7 += massive[i + 6];
            }
            else*/ if (i + 5 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
                sum4 += massive[i + 3];
                sum5 += massive[i + 4];
                sum6 += massive[i + 5];
            }
            else if (i + 4 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
                sum4 += massive[i + 3];
                sum5 += massive[i + 4];
            }
            else if (i + 3 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
                sum4 += massive[i + 3];
            }
            else if (i + 2 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
                sum3 += massive[i + 2];
            }
            else if (i + 1 < N) {
                sum1 += massive[i];
                sum2 += massive[i + 1];
            }
            else 
            sum1 += massive[i];
        }
        aver = (sum1 + sum2 + sum3 + sum4 + sum5 + sum6) / N;
        // Засекаем время конца
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        //  Выводим результат
        std::cout << "Time consumed: " << duration.count() << " us"<< std::endl;
    }
    //std::cout << "Average number: " << aver << std::endl;
    return 0;
}