    return v;
}

#ifdef TESTMAIN
#include <stdio.h>

int main(void) {
    char buf[32];

    sprintf(buf,"ciaoroma");
    memrev16(buf);
    printf("%s\n", buf);
