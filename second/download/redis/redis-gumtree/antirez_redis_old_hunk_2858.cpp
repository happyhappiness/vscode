
/* Return intset length */
uint32_t intsetLen(intset *is) {
    return is->length;
}

/* Return intset blob size in bytes. */
size_t intsetBlobLen(intset *is) {
    return sizeof(intset)+is->length*is->encoding;
}

#ifdef INTSET_TEST_MAIN
#include <sys/time.h>

void intsetRepr(intset *is) {
    int i;
    for (i = 0; i < is->length; i++) {
        printf("%lld\n", (uint64_t)_intsetGet(is,i));
    }
    printf("\n");
