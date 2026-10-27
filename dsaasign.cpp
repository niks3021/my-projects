#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

// i. T(n) = T(n-1) + 1
long long recurrence1(int n) {
    if (n <= 1) return 1;
    return recurrence1(n - 1) + 1;
}

// ii. T(n) = T(n-1) + n
long long recurrence2(int n) {
    if (n <= 1) return 1;
    return recurrence2(n - 1) + n;
}

// iii. T(n) = T(n-1) + n^2
long long recurrence3(int n) {
    if (n <= 1) return 1;
    return recurrence3(n - 1) + (n * n);
}

// iv. T(n) = T(n-1) + log(n)
double recurrence4(int n) {
    if (n <= 1) return 1.0;
    return recurrence4(n - 1) + std::log(n);
}

template <typename Func>
long long measureRecurrenceTime(Func f, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    f(n);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    std::cout << "n\tT1(T(n-1)+1)\tT2(T(n-1)+n)\tT3(T(n-1)+n^2)\tT4(T(n-1)+log n)\n";
    // Keep n within reasonable bounds (e.g., up to 20) to prevent deep recursion issues
    std::vector<int> nValues = {1, 2, 3, 5, 10, 15, 20};

    for (int n : nValues) {
        long long t1 = measureRecurrenceTime(recurrence1, n);
        long long t2 = measureRecurrenceTime(recurrence2, n);
        long long t3 = measureRecurrenceTime(recurrence3, n);
        long long t4 = measureRecurrenceTime(recurrence4, n);

        std::cout << n << "\t" << t1 << "\t\t" << t2 << "\t\t" << t3 << "\t\t" << t4 << "\n";
    }

    return 0;
}