#include "error.h"
#include <cstdio>

extern int line, column;

void Er(int i) {
    ++errors;
    printf("[%d, %d] ERROR %d\n", line, column, i);
}
