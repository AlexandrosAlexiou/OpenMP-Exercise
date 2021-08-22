//
//  main.c
//  OpenMP-Primes
//
//  Created by Alexandros Alexiou on 18/4/20.
//  Copyright © 2020 Alexandros Alexiou. All rights reserved.
//
#include <iostream>
#include <omp.h>

#define UPTO 1000000
#define NUM_THREADS 16
#define CHUNK_SIZE  5

long int count,      /* number of primes */
         lastprime;  /* the last prime found */


void serial_primes(long int n) {
    long int i, num, divisor, quotient, remainder;

    if (n < 2) return;
    count = 1;                         /* 2 is the first prime */
    lastprime = 2;

    for (i = 0; i < (n-1)/2; ++i) /* For every odd number */
    {
        num = 2*i + 3;

        divisor = 1;
        do
        {
            divisor += 2;                  /* Divide by the next odd */
            quotient  = num / divisor;
            remainder = num % divisor;
        } while (remainder && divisor <= quotient);  /* Don't go past sqrt */

        if (remainder || divisor == num) /* num is prime */
        {
            count++;
            lastprime = num;
        }
    }
}


void openmp_primes(long int n) {
    long int i = 0, num, divisor, quotient, remainder;

    if (n < 2) return;
    count = 1;                         /* 2 is the first prime */
    lastprime = 2;

#pragma omp parallel for private(i, num, divisor, quotient, remainder) reduction(+: count) reduction(max: lastprime) num_threads(NUM_THREADS) schedule(static, CHUNK_SIZE)
    for (i = 0; i < (n-1)/2; ++i) /* For every odd number */
    {
        num = 2*i + 3;

        divisor = 1;
        do
        {
            divisor += 2;                  /* Divide by the next odd */
            quotient  = num / divisor;
            remainder = num % divisor;
        } while (remainder && divisor <= quotient);  /* Don't go past sqrt */
        
        if (remainder || divisor == num) /* num is prime */
        {
            count++;
            lastprime = num;
        }
    }
}


int main()
{
    double start = 0.0;
    double end   = 0.0;
    std::cout << "Serial and parallel prime number calculations:\n\n" << std::endl;
    /* Time the following to compare performance
     */
    start = omp_get_wtime();
    serial_primes(UPTO);
    end   = omp_get_wtime();
    std::cout << "[serial] count = "+ std::to_string(count) +", last = " + std::to_string(lastprime) + " (time = "+ std::to_string(end - start) +" seconds)\n" << std::endl;
    start = omp_get_wtime();
    openmp_primes(UPTO);
    end   = omp_get_wtime();
    std::cout << "[openmp] count = "+ std::to_string(count) +", last = " + std::to_string(lastprime) + " (time = "+ std::to_string(end - start) +" seconds)\n" << std::endl;
    return 0;
}
