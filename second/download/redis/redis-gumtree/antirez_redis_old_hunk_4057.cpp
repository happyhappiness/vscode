void ziplistRepr(unsigned char *zl) {
    unsigned char *p, encoding;
    unsigned int l, lsize;
    long long value;

    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
    p = ziplistHead(zl);
