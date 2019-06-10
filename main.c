#include "primetest_32u.h"
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <inttypes.h>


/***
 * Tests the prime checking speed in a given range.
 * @param lower The lower bound included in the test.
 * @param upper The upper bound exclusive of the test.
 * @param iter The number of iterations to attempt.
 * @return The integers/second checked
 */
double testrange(unsigned lower, unsigned upper, unsigned iter) {
    unsigned range_size = upper - lower;

    double start = omp_get_wtime();
    for (unsigned j = 0; j < iter; ++j) {
        for (unsigned i = lower; i < upper; ++i) {
            isprime_int(i);
        }
    }
    double stop = omp_get_wtime();
    return ((double)iter * range_size) / (stop - start);
}

void verifier(void) {
    for (size_t i = 0; i < uint16_primes_len; ++i)
    {
        uint16_t n = primes_u16[i];
        if (!isprime_u16(n)) printf("%" PRIu16 " is a prime but failed check\n", n);
    }
}

int main(int argc, char** argv) {
    printf("sizeof(primes_u16) = %zu\n", sizeof(primes_u16) / sizeof(primes_u16[0]));

    unsigned test_vectors[] = {
             1U<<0, 1U<<8,
             1U<<9, 1U<<10, 1U<<11, 1U<<12, 1U<<13, 1U<<14, 1U<<15, 1U<<16,
            1U<<17, 1U<<18, 1U<<19, 1U<<20, 1U<<21, 1U<<22, 1U<<23, 1U<<24,
            1U<<25, 1U<<26, 1U<<27, 1U<<28, 1U<<29, 1U<<30, 1U<<31, (1ULL<<32)-1};
    unsigned test_iters[] = {
            1<<18, 1<<18,
            1<<17, 1<<17, 1<<16, 1<<15, 1<<14, 1<<14, 1<<13, 1<<12, 1<<11,
            1<<11, 1<<10, 1<<10,  1<<9,  1<<9,  1<<8,  1<<7,  1<<3,  1<<2,
             1<<2,  1<<1,  1<<1,  1<<1,     1,     1,     1,     1,      1
    };

    //size_t test_vectors_len = sizeof(test_vectors)/sizeof(test_vectors[0]);

#pragma omp parallel for
        for (int i = 10; i < 12; ++i) {
            printf("testing range [%u, %u) in thread %d\n", test_vectors[i], test_vectors[i+1], omp_get_thread_num());
            printf("[%u,%u) %.0fk / s\n", test_vectors[i], test_vectors[i + 1],
                   testrange(test_vectors[i], test_vectors[i + 1], test_iters[i]) / 1000);
        }
}
