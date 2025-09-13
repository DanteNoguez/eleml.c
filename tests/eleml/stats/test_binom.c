#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "stats/binom.h"

static int tests_run = 0;
static int tests_failed = 0;

static void expect_true(const char *name, bool condition) {
    tests_run++;
    if (!condition) {
        tests_failed++;
        printf("FAIL: %s\n", name);
    }
}


static void expect_near(const char *name, float actual, float expected, float eps) {
    tests_run++;
    float diff = fabsf(actual - expected);
    if (diff > eps) {
        tests_failed++;
        printf("FAIL: %s (actual=%.9f expected=%.9f diff=%.9f eps=%.9f)\n",
               name, actual, expected, diff, eps);
    }
}

static void test_pmf_known_value(void) {
    float v = pmf(2, 3, 0.7f);
    expect_near("pmf(2,3,0.7) == 0.441", v, 0.441f, 1e-6f);
}

static void test_cdf_known_value(void) {
    float v = cdf(2, 3, 0.7f);
    expect_near("cdf(2,3,0.7) == 0.657", v, 0.657f, 1e-6f);
}

static void test_cdf_range(void) {
    float v = cdf(4, 5, 0.5f) - cdf(1, 5, 0.5f);
    expect_near("pmf(4,5,0.5) - cdf(1,5,0.5) == 0.78125", v, 0.78125f, 1e-6f);
}

static void test_pmf_normalizes_to_one(void) {
    int n = 5;
    float p = 0.3f;
    float sum = 0.0f;
    for (int k = 0; k <= n; k++) {
        sum += pmf(k, n, p);
    }
    expect_near("sum_k pmf(k,n,p) == 1", sum, 1.0f, 1e-6f);
}

static void test_cdf_monotone_and_limits(void) {
    int n = 6;
    float p = 0.42f;
    float prev = 0.0f;
    for (int k = 0; k <= n; k++) {
        float cur = cdf(k, n, p);
        expect_true("cdf is non-decreasing", cur + 1e-9f >= prev);
        prev = cur;
    }
    expect_near("cdf(n,n,p) == 1", prev, 1.0f, 1e-6f);
}

int main(void) {
    test_pmf_known_value();
    test_cdf_known_value();
    test_pmf_normalizes_to_one();
    test_cdf_monotone_and_limits();
    test_cdf_range();
    
    if (tests_failed == 0) {
        printf("OK: %d tests\n", tests_run);
        return 0;
    } else {
        printf("FAILED: %d/%d tests failed\n", tests_failed, tests_run);
        return 1;
    }
}
