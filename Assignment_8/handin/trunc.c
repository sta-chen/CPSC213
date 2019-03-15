//
//  trunc.c
//
//
//  Created by Sta_C on 2019-03-13.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "list.h"

// Step 2
void stringToInteger(element_t* outv, element_t inv) {
    int** out = (int**) outv;
    char* in = inv;
    char* end;
    *out = malloc(sizeof(int*));
    **out = strtol(in, &end, 10);
    if (*end) {
        **out = -1;
    }
}

// Step 3
void keepString(element_t* outv, element_t siv, element_t iiv) {
    char** out = (char**) outv;
    char* si = (char*) siv;
    int* ii = (int*) iiv;
    
    *out = *ii < 0 ? si : 0;
}

// Step 4
int isNotNegative(element_t num) {
    int* i = (int*) num;
    return *i >= 0;
}

// Step 5
int isNotNull(element_t str) {
    return str != NULL;
}

// Step 6
void truncate(element_t* outv, element_t siv, element_t iiv) {
    char** out = (char**) outv;
    char* si = (char*) siv;
    int* ii = (int*) iiv;
    
    *out = strdup(si);
    
    if (strlen(*out) > *ii) {
        (*out)[*ii] = 0;
    }
}

// Step 7
void printString(element_t str) {
    char* s = (char*) str;
    printf("%s\n", s? s : "NULL");
}

// Step 8 TODO
// foldl need 3 args
// size correct
//void findSize(element_t* outv, element_t nop, element_t inv) {
//    intptr_t* out = (intptr_t*) outv;
//    intptr_t in = (intptr_t) inv;
//    *out += in + 1;
//}

// foldl need 3 args
//TODO URGENT
void intoSingleArray(element_t* outv, element_t av, element_t bv) {
//    char* a = (char*) av;
//    char* b = (char*) bv;
//    strcat(a, b);
//    strcat(a, " ");
    char** out = (char**) outv;
    char* b = bv;
    *out = realloc(*out, strlen(*out) + strlen(b) + 2);
    if (strlen(*out)) {
        strcat(*out, " ");
    }
    strcat(*out, b);
}


// Step 9
void max(element_t* outv, element_t av, element_t bv) {
    int** out = (int**) outv;
    int* a = (int*) av;
    int* b = (int*) bv;
    **out = (*a > *b) ? *a : *b;
}

void printInt(element_t numv) {
    int* num = (int*) numv;
    printf("%d\n", *num);
}

int main(int argc, char** argv) {
    struct list* arg_list = list_create();
    for (int i = 1; i < argc; i++) {
        list_append(arg_list, argv[i]);
    }
    
    // Step 2
    struct list* i_num_list = list_create();
    list_map1(stringToInteger, i_num_list, arg_list);
    
    // Step 3
    struct list* i_str_list = list_create();
    list_map2(keepString, i_str_list, arg_list, i_num_list);
    
    // Step 4
    struct list* filtered_num_list = list_create();
    list_filter(isNotNegative, filtered_num_list, i_num_list);
    
    // Step 5
    struct list* filtered_str_list = list_create();
    list_filter(isNotNull, filtered_str_list, i_str_list);
    
    // Step 6
    struct list* truncated_list = list_create();
    list_map2(truncate, truncated_list, filtered_str_list, filtered_num_list);
    
    list_foreach(printString, truncated_list);

    
    // Step 8 TODO
    
//    int length = 0, *lp = &length;
//    list_foldl(findSize, (element_t*) &lp, filtered_num_list);
//
//    char r[length + 1];
//    char* string = r;
//    string[0] = '\0';
//    char** sp = &string;
//    list_foldl(intoSingleArray, (element_t*) sp, truncated_list);
//    printf("%s\n", r);
    
    char* s = malloc(1);
    s[0] = 0;
    list_foldl(intoSingleArray, (element_t*) &s, truncated_list);
    printf("%s\n", s);
    free(s);
    
    // Step 9
    int v = -1;
    int* vp = &v;
    list_foldl(max, (element_t*) &vp, filtered_num_list);
    printf("%d\n", v);

    list_foreach(free, truncated_list);
    list_foreach(free, i_num_list);
    
    list_destroy(arg_list);
    list_destroy(i_num_list);
    list_destroy(i_str_list);
    list_destroy(filtered_num_list);
    list_destroy(filtered_str_list);
    list_destroy(truncated_list);
}
