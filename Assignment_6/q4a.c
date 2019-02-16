//
//  q4a.c
//  
//
//  Created by Sta_C on 2019-02-16.
//

#include <stdio.h>
int a[] = (int[10]) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void bar(int m, int n) {
    a[n] = a[n] + m;
}

void foo() {
    int a = 1;
    int b = 2;
    bar(3, 4);
    bar(1, 2);
}



int main(int argc, char** argv) {
    foo();
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    
    return 0;
}
