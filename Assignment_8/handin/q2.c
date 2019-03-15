//
//  q2.c
//  
//
//  Created by Sta_C on 2019-03-14.
//

#include <stdio.h>

int q2(int a, int b, int c) {
    int result;
    switch (a) {
        case 10:
            result = b + c;
            break;
        case 12:
            result = b - c;
            break;
        case 14:
            if (b > c) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        case 16:
            if (b < c) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        case 18:
            if (b == c) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        default:
            result = 0;
    }
    return result;
}

