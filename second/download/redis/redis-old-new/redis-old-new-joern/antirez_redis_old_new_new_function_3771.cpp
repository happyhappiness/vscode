void intsetRepr(intset *is) {
    int i;
    for (i = 0; i < is->length; i++) {
        printf("%lld\n", (uint64_t)_intsetGet(is,i));
    }
    printf("\n");
}