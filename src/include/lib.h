#ifndef LIB_H
#define LIB_H

#include "types.h"

size_t k_strlen(const char* str);
int    k_strcmp(const char* s1, const char* s2);

void* k_memset(void* s, int c, size_t n);
void* k_memcpy(void* dest, const void* src, size_t n);

#endif