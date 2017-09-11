}

/* Test main */
#ifdef REDIS_TEST
#include <stdio.h>

#define UNUSED(x) (void)(x)
int crc64Test(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    printf("e9c6d914c4b8d9ca == %016llx\n",
        (unsigned long long) crc64(0,(unsigned char*)"123456789",9));
    return 0;
