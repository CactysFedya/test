#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

void testThread(uint64_t *inPtrData, int number) {
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t *ptr = inPtrData;
    for(uint64_t i = 0; i < 10000000; ++i)
    {
        ++*ptr;
        ++ptr;
    }
    // Запоминаем время окончания
    auto end = std::chrono::high_resolution_clock::now();
    // Вычисляем разницу во времени
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
   // Выводим результат
   std::cout << "Номер потока: " << number << " " << duration.count() << " секунд " << std::endl;
}


int main()
{
    {
        uint64_t size = 100000000;
        uint64_t* a = new uint64_t[size];
        for (int64_t i = 0; i < size; ++i) {
            a[i] = i;
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (int64_t i = 0; i < size; ++i) {
            ++a[i];
        }
        auto end = std::chrono::high_resolution_clock::now();
        // Вычисляем разницу во времени
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
       // Выводим результат
        std::cout << "Время выполнения без потоков: " << duration.count() << " секунд " << std::endl;
        delete[] a;
    }

    {
        uint64_t size = 100000000;
        uint64_t* a = new uint64_t[size];
        for (int64_t i = 0; i < size; ++i) {
            a[i] = i;
        }
        auto start = std::chrono::high_resolution_clock::now();
        vector<thread> threads;
        for(int i = 0; i < 10; i += 1)
        {
            threads.push_back(std::thread (testThread, a + i * 10000000, i));
        }

        for(int i = 0; i < 10; ++i)
        {
            threads[i].join();
        }

        // Запоминаем время окончания
        auto end = std::chrono::high_resolution_clock::now();
        // Вычисляем разницу во времени
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
       // Выводим результат
        std::cout << "Время выполнения без потоков: " << duration.count() << " секунд ";
        delete[] a;
    }

    return 0;
}
