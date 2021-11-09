//
// Created by ksenia on 08.11.2021.
//

#ifndef IZ2_LIBS_ARRAY_FUNCS_ARRAY_FUNCS_H_
#define IZ2_LIBS_ARRAY_FUNCS_ARRAY_FUNCS_H_

int get_int(FILE *f);
int *create_array(FILE *f, size_t *arr_len);
int free_array(int *arr);

#endif //IZ2_LIBS_ARRAY_FUNCS_ARRAY_FUNCS_H_
