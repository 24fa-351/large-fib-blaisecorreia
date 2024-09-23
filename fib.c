#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>

typedef unsigned long long fib_int;
fib_int fib_recursive(fib_int n) {
    if (n <= 1) {
        return n;
    }
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}
fib_int fib_iterative(fib_int n) {
    if (n <= 1) {
        return n;
    }
    
    fib_int a = 0, b = 1, next;
    for (fib_int i = 2; i <= n; i++) {
        if (__builtin_add_overflow(a, b, &next)) {
            printf("Overflow detected at Fibonacci(%llu)\n", i);
            exit(1);
        }
        a = b;
        b = next;
    }
    return b;
}

int check_overflow(fib_int a, fib_int b) {
    fib_int result;
    return __builtin_add_overflow(a, b, &result);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <integer> <r/i>\n", argv[0]);
        return 1;
    }

    fib_int N = atoll(argv[1]);
    char method = argv[2][0];

    fib_int result;

    clock_t start, end;
    double cpu_time_used;

    if (method == 'r') {
        start = clock();
        result = fib_recursive(N);
        end = clock();
    } else if (method == 'i') {
        start = clock();
        result = fib_iterative(N);
        end = clock();
    } else {
        printf("Error: Invalid method. Use 'r' for recursive or 'i' for iterative.\n");
        return 1;
    }

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("The %lluth Fibonacci number is: %llu\n", N, result);
    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}