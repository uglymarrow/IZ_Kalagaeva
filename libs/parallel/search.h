//
// Created by ksenia on 08.11.2021.
//

#ifndef IZ2_LIBS_PARALLEL_SEARCH_H_
#define IZ2_LIBS_PARALLEL_SEARCH_H_

int search(int *arr, size_t arr_len);
int search_proc(const int *arr, int *max_diff, int *diff_time, size_t start, size_t finish);

#endif //IZ2_LIBS_PARALLEL_SEARCH_H_
