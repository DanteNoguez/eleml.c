#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ops.h"

float pmf(int k, int n, float p) {
    /*
     * Calculates the probability of observing k successes in n trials with a probability of success p.
     */
    if (p < 0 || p > 1) {
        fprintf(stderr, "p must be between 0 and 1\n");
        exit(EXIT_FAILURE);
    }
    if (n < 0) {
        fprintf(stderr, "n must be greater than 0\n");
        exit(EXIT_FAILURE);
    }
    if (k < 0 || k > n) {
        fprintf(stderr, "k must be between 0 and n\n");
        exit(EXIT_FAILURE);
    }
    float output = combination(n, k) * pow(p, k) * pow(1-p, n-k);
    return output;
}

float cdf(int k, int n, float p) {
    /*
     * Calculates the cumulative distribution function of a binomial distribution.
     * This is the sum of the probability mass function from 0 to k, 
     * where k is the number of successes, n is the number of trials, and p is the probability of success.
     */
    float output = 0;
    for (int i = 0; i <= k; i++) {
        output += pmf(i, n, p);
    }
    return output;

}
