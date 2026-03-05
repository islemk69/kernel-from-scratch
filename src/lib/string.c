#include "../include/lib.h"

size_t k_strlen(const char* str) {
    int i = 0;
    while (str[i]) i++;
    return i;
}

int k_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}