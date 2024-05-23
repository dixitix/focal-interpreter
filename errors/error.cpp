#include "error.h"
#include <cstdio>

extern int line, column;

void Er(int i) {
    ++errors;
    printf("[%d, %d] ERROR: %s\n", line, column, error_messages[i]);
}
