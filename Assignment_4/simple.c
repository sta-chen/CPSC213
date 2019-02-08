//
//  simple.c
//  
//
//  Created by Sta_C on 2019-01-29.
//

#include <stdlib.h>
#include <stdio.h>

void foo(char* s) {
    printf("%s World\n", s);
}

int main(int argc, char** argv) {
    foo("Hello");
}
