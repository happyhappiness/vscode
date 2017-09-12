    }
}

int main(int argc, char **argv) {
    unsigned char *zl, *p;
    unsigned char *entry;
    unsigned int elen;
    long long value;
    sds s;

    zl = createIntList();
    ziplistRepr(zl);

    zl = createList();
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_HEAD);
    printf("Pop head: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    printf("Get element at index 3:\n");
