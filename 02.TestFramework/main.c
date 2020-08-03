/*************************************************************************
	> File Name: main.c
	> Author: wpz
	> Mail: 1024827983@qq.com
	> Created Time: 日 10/ 7 11:32:37 2018
 ************************************************************************/
#include <stdio.h>
#include "newton.h"
#include "two_points.h"
#include "test.h"
#ifdef TEST_FUNC
    #include "testcase1.h"
    #include "testcase2.h"
#endif

int main() {
    newton(4);
    two_points(1, 5, 2);
    printf("hello world\n");
    return RUN_ALL_TEST();
}
