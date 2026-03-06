#include "../include/lib.h"
#include "types.h"

char *k_itoa(int value, char *str, int base) {
    char *rc;
    char *ptr;
    char *low;
    char *digits = "0123456789ABCDEF";

    rc = ptr = str;
    if (value < 0 && base == 10) {
        *ptr++ = '-';
    }
    low = ptr;
    do {
        *ptr++ = digits[value % base < 0 ? -(value % base) : value % base];
        value /= base;
    } while (value);
    *ptr-- = '\0';
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

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