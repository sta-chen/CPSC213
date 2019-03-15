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
    intptr_t* out = (intptr_t*) outv;
    char* in = inv;
    char* end;
    *out = strtol(in, &end, 10);
    if (*end) {
        *out = -1;
    }
}

// Step 3
void keepString(element_t* outv, element_t siv, element_t iiv) {
    char** out = (char**) outv;
    char* si = (char*) siv;
    intptr_t ii = (intptr_t) iiv;
    
    *out = ii < 0 ? si : 0;
}

// Step 4
int isNotNegative(element_t num) {
    intptr_t i = (intptr_t) num;
    return i >= 0;
}

// Step 5
int isNotNull(element_t str) {
    return str != NULL;
}

// Step 6
void truncate(element_t* outv, element_t siv, element_t iiv) {
    char** out = (char**) outv;
    char* si = (char*) siv;
    intptr_t ii = (intptr_t) iiv;
    
    *out = strdup(si);
    
    if (strlen(*out) > ii) {
        (*out)[ii] = 0;
    }
}

// Step 7
void printString(element_t str) {
    char* s = (char*) str;
    printf("%s\n", s? s : "NULL");
}

// Step 8 TODO




// Step 9
void max(element_t* outv, element_t av, element_t bv) {
    intptr_t* out = (intptr_t*) outv;
    intptr_t a = (intptr_t) av;
    intptr_t b = (intptr_t) bv;
    *out = (a > b) ? a : b;
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
    list_foreach(free, truncated_list);
    
   
    
    // Step 9
    int* v;
    *v = -1;
    list_foldl(max, (element_t*) &v, filtered_num_list);
    printf("%ld\n", *v);
    
    list_destroy(arg_list);
    list_destroy(i_num_list);
    list_destroy(i_str_list);
    list_destroy(filtered_num_list);
    list_destroy(filtered_str_list);
    list_destroy(truncated_list);
}
