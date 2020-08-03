/*************************************************************************
	> File Name: is_prime.c
	> Author: wpz
	> Mail: 1024827983@qq.com
	> Created Time: 日 10/ 7 11:35:37 2018
 ************************************************************************/
#include <math.h>
#include <stdio.h>
#include "test.h"
#include "newton.h"

double fn(double x, double n) {
    return x * x - n;
}

double f_prime(double x) {
    return 2 * x;
}

double newton(double n) {
    double x = 1.0;
    #define EPS 1e-7
    while (fabs(fn(x, n)) > EPS) {
        x -= fn(x, n) / f_prime(x);
        #undef EPS
    }
    return x;
}

/*int main() {
    double x;
    while (scanf("%lf", &x) != EOF) {
        printf("%lf\n", newton(x, fn, f_prime));
    }
    return 0;
}*/
