//
//  q4a.c
//  
//
//  Created by Sta_C on 2019-02-16.
//

#include <stdio.h>
int a[] = (int[10]) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int* p = a;

void bar(int m, int n) {
    p[n] = p[n] + m;
}

void foo() {
    int a, b;
    a = 1;
    b = 2;
    bar(3, 4);
    bar(1, 2);
}



int main(int argc, char** argv) {
    foo();
    for (int i = 0; i < 10; i++) {
        printf("%d\n", a[i]);
    }
    
    return 0;
}
