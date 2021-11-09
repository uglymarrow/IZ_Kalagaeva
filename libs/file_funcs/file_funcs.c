#include "file_funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

FILE *open_file(const char *file_path) {
  FILE *f = NULL;
  f = fopen(file_path, "r");
  if (f != NULL)
    return f;
  else {
    fprintf(stderr, "Can't open file");
    exit(EXIT_FAILURE);
  }
}

int close_file(FILE *f) {
  if (!f) {
    fprintf(stderr, "File doesn't exist");
    exit(EXIT_FAILURE);
  }

  if (fclose(f) == EXIT_SUCCESS)
    return EXIT_SUCCESS;
  else {
    fprintf(stderr, "Can't close file");
    exit(EXIT_FAILURE);
  }
}




