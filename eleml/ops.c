int factorial(int n) {
    int output = 1;
    for (int i = 1; i <= n; i++) {
        output *= i;
    }
    return output;
}

float combination(int n, int k) {
    float output = factorial(n) / (factorial(k) * factorial(n-k));
    return output;
}