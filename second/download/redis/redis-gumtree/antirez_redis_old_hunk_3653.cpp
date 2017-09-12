
#ifdef ZIPLIST_TEST_MAIN
#include <sys/time.h>

unsigned char *createList() {
    unsigned char *zl = ziplistNew();
