#include "string.h"

size_t strlen(const char *str) {
    size_t s = 0;
    for (; str[s]; s++);
    return s;
}