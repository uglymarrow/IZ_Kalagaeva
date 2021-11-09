//
// Created by ksenia on 02.11.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "search.h"

#define PROCS_COUNT sysconf(_SC_NPROCESSORS_ONLN)

int search_proc(const int *arr, int *max_diff, int *diff_time, size_t start, size_t finish) {
  for (size_t i = start+1; i <= finish; i++)
    if ((arr[i] - arr[i - 1]) > *max_diff) {
      *max_diff = arr[i] - arr[i - 1];
      *diff_time = (int)i;
    }
  if (*diff_time == 0) {
    printf("Положительных скачков температуры не было");
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
}

int search(int *arr, size_t arr_len) {
  if (!arr) {
    fprintf(stderr, "Function parallel/search. Array doesn't exist");
    exit(EXIT_FAILURE);
  }

  int *max_diff = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  int *diff_time = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  *max_diff = 0;
  *diff_time = 0;
  pid_t *pid_arr = (pid_t *)calloc(PROCS_COUNT,sizeof(pid_t) );
  size_t part_len = arr_len / PROCS_COUNT;

  for (int i = 0; i < PROCS_COUNT; ++i) {
    pid_arr[i] = fork();
    if (pid_arr[i] == -1) {
      printf("fork failed\n");
      exit(EXIT_FAILURE);
    }
    if (pid_arr[i] == 0) {
      if (i == PROCS_COUNT - 1) {
        search_proc(arr, max_diff, diff_time, part_len * i, arr_len - 1);
        exit(EXIT_SUCCESS);
      } else {
        search_proc(arr, max_diff, diff_time, part_len * i, part_len * (i + 1));
        exit(EXIT_SUCCESS);
      }
    } else {
      int status;
      if (waitpid(pid_arr[i], &status, 0) != pid_arr[i])
        exit(EXIT_FAILURE);
    }
  }

  int result = *diff_time;

  free(pid_arr);
  munmap(diff_time, sizeof(int));
  munmap(max_diff, sizeof(int));

  return result;
}
