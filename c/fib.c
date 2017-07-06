#include <assert.h>

int fib(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
};


// int main() {
//     int fib_len = 21;
//     int fibs[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765};

//     int idx;

//     for (idx = 0; idx < fib_len; idx++) {
//         int tmp = fib(idx);
//         assert(tmp == fibs[idx]);
//     }
// }