#include <stdio.h>
int main(void) {
    printf("e9c6d914c4b8d9ca == %016llx\n",
        (unsigned long long) crc64((unsigned char*)"123456789",9));
    return 0;
}
#endif
