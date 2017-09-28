
uint64_t intrev64(uint64_t v) {
    memrev64(&v);
    return v;
}

#ifdef TESTMAIN
#include <stdio.h>

int main(void) {
    char buf[32];

    sprintf(buf,"ciaoroma");
    memrev16(buf);
    printf("%s\n", buf);

    sprintf(buf,"ciaoroma");
    memrev32(buf);
