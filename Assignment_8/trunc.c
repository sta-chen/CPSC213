//
//  trunc.c
//  
//
//  Created by Sta_C on 2019-03-13.
//

#include <stdio.h>
#include "list.h"

// Step 2
void stringToInteger(element_t* outv, element_t inv) {
    int** out = (int**) outv;
    char* in = inv;
    char* end;
    *out = strtol(in, &end, 10);
    if (*end != NULL) {
        *out = -1;
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
void accumulate_size(element_t* out, element_t ignore, element_t num_in) {
    *(int*)out += (*(int*)num_in) + 1;
}

/*
 Function for Step 8 (concatenating the string)
 */
void concatenate_string(element_t* out, element_t ignore, element_t in) {
    char* out_string = *out;
    char* in_string = in;
    
    // Find the start index to copy characters to
    int out_index = 0;
    while (out_string[out_index] != '\0') {
        out_index++;
    }
    
    // copy the string
    int in_index = 0;
    while (in_string[in_index] != '\0') {
        out_string[out_index] = in_string[in_index];
        out_index++;
        in_index++;
    }
    // add white space and '\0'
    out_string[out_index] = ' ';
    out_string[out_index + 1] = '\0';
}

// Step 9
void max(element_t* outv, element_t av, element_t bv) {
    int** out = (int**) outv;
    int* a = (int*) av;
    int* b = (int*) bv;
    *out = (*a > *b) ? a : b;
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
    
    // Step 8 TODO
    int size = 0;
    list_foldl(accumulate_size, (void*) &size, filtered_number_list);
    
    char* string = malloc(sizeof(char) * size + 1);
    
    // Set the initial char to NULL so concatenate_string knows where to start
    string[0] = '\0';
    
    list_foldl(concatenate_string, (void*) &string, truncated_string_list);
    
    // Currently, the string is not null terminated, and string[size] = ' '
    // So, just change it to '\0'
    string[size] = '\0';
    // Note that string ends with 2 NULLs but it doesn't matter because free
    // doesn't care; no memory issues.
    
    // Print it as per instruction
    print_string(string);
    
    // Step 9
    int* v;
    *v = -1;
    list_foldl(max, (element_t*) &v, filtered_num_list);
    printf("%ld\n", *v);
    
    free(string);
    list_destroy(arg_list);
    list_destroy(i_num_list);
    list_destroy(i_str_list);
    list_destroy(filtered_num_list);
    list_destroy(filtered_str_list);
    list_destroy(truncated_list);
}
