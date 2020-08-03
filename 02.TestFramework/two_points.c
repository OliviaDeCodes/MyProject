/*************************************************************************
	> File Name: add.c
	> Author: wpz
	> Mail: 1024827983@qq.com
	> Created Time: 日 10/ 7 11:36:20 2018
 ************************************************************************/

#include <stdio.h>
#include "test.h"
#include "two_points.h"

int two_points(int x1, int x2, int y) {
    int temp = 0;
    int head = x1,tail = x2, mid;
    if (head > tail) {
        temp = head;
        head = tail;
        tail = temp;
    }
    mid = (head + tail) / 2;
    //if (mid == y) return 1;
    while (head < tail && mid != y) {
        //if (mid == y) return 1;
        if (mid < y) head = mid + 1;
        else if (mid > y) tail = mid;
        mid = (head + tail) / 2;
    }
    if (mid == y) return 1;
    return 0;
}

