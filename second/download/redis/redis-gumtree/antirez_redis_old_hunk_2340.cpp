#include "sds.h"
#include "zmalloc.h"

sds sdsnewlen(const void *init, size_t initlen) {
    struct sdshdr *sh;

