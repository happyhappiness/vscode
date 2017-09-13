int main(int argc, char **argv) {
    unsigned char *zl;
    sds s;

    zl = ziplistNew();
    zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
    ziplistRepr(zl);
    zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
    ziplistRepr(zl);
    zl = ziplistPush(zl, (unsigned char*)"hello", 5, ZIPLIST_HEAD);
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_HEAD);
    printf("Pop head: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    return 0;
}