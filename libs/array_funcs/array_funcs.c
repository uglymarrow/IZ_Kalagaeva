//
// Created by ksenia on 08.11.2021.
//

#include <stdio.h>
#include <stdlib.h>

#include "array_funcs.h"

int get_int(FILE *f) {
  if (!f) {
    fprintf(stderr, "File doesn't exist");
    exit(EXIT_FAILURE);
  }

  int result = 0;
  if (fscanf(f, "%i", &result) == EOF) return EOF;
//  if (fscanf(f, "%c", &result) <= 0) {
//    fprintf(stderr, "File reading error");
//    exit(EXIT_FAILURE);
//  }

  return result;
}

int *create_array(FILE *f, size_t *arr_len) {
  if (!f) {
    fprintf(stderr, "File doesn't exist");
    exit(EXIT_FAILURE);
  }

  int *arr = NULL;
  size_t buffer = 2;
  arr = (int *) malloc(buffer * sizeof(int));
  if (!arr) {
    fprintf(stderr, "Memory allocation error");
    exit(EXIT_FAILURE);
  } else {
    int num = get_int(f);
    size_t i = 0;
    do {
      if (i > buffer) {
        buffer *= 2;
        arr = (int *) realloc(arr, buffer * sizeof(int));
      }
      arr[i] = num;
      i++;
      num = get_int(f);
    } while (num != EOF);
    *arr_len = i;
  }
  return arr;
}

int free_array(int *arr) {
  if (!arr) {
    fprintf(stderr, "Memory allocation error");
    return EXIT_FAILURE;
  } else {
    free(arr);
    return EXIT_SUCCESS;
  }
}
