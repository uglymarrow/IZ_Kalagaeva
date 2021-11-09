//
// Created by ksenia on 09.11.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "search.h"
// Пусть в файле лежит информация о температуре за каждую секунду/минуту/час
int search (int* arr, size_t arr_len){
  float max_diff = 0;
  int diff_time = 0;
  for (size_t i = 1; i < arr_len; i++)
    if ((arr[i] - arr[i-1]) > max_diff) {
      max_diff = arr[i] - arr[i-1];
      diff_time = i;
    }
  if (diff_time == 0) {
    printf("Положительных скачков температуры не было");
    return EXIT_FAILURE;
  } else {
    return diff_time;
  }
}

