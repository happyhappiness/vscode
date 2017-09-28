
uint64_t intrev64(uint64_t v) {
    memrev64(&v);
    return v;
}

#ifdef REDIS_TEST
#include <stdio.h>

#define UNUSED(x) (void)(x)
int endianconvTest(int argc, char *argv[]) {
    char buf[32];

    UNUSED(argc);
    UNUSED(argv);

    sprintf(buf,"ciaoroma");
    memrev16(buf);
    printf("%s\n", buf);

    sprintf(buf,"ciaoroma");
    memrev32(buf);
