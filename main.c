//Вариант #26
//Сравните и выведите в консоль время работы последовательного и параллельного с использованием нескольких процессов алгоритмов,
//каждый из которых выделяет в динамической памяти числовой массив размером 100 Мб, заполненный положительными или отрицательными значениями температуры за день,
//после чего выполняет поиск времени, когда произошел самый резкий положительный скачок температуры.

#include <dlfcn.h> //для работы с динамической библиотекой
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "libs/array_funcs/array_funcs.h"
#include "libs/file_funcs/file_funcs.h"
#include "libs/parallel/search.h"

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "A txt file must be sent to the input");
    exit(EXIT_FAILURE);
  }

  FILE *f = open_file(argv[1]);

  size_t arr_len = 0;
  int *arr = create_array(f, &arr_len);
  close_file(f);

  clock_t begin_time = clock();
  search(arr, arr_len);
  clock_t end_time = clock();
  free_array(arr);
  printf("TIME: %li", end_time - begin_time);
  printf("\nEnd");

  return EXIT_SUCCESS;
}