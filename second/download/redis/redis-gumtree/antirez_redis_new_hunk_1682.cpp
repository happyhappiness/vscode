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
