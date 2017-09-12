}

void ziplistRepr(unsigned char *zl) {
    unsigned char *p;
    unsigned int l;

    printf("{bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
    p = ziplistHead(zl);
    while(*p != ZIP_END) {
        l = zipDecodeLength(p);
        printf("{key %u}",l);
        p += zipEncodeLength(NULL,l);
        fwrite(p,l,1,stdout);
        printf("\n");
        p += l;
    }
