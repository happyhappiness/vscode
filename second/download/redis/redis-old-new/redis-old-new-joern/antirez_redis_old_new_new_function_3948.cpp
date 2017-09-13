void ziplistRepr(unsigned char *zl) {
    unsigned char *p, encoding;
    unsigned int l, lsize;
    long long value;

    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
    p = ziplistHead(zl);
    while(*p != ZIP_END) {
        l = zipDecodeLength(p,&lsize);
        printf("{header %u, payload %u} ",lsize,l);
        encoding = ZIP_ENCODING(p);
        p += lsize;
        if (encoding == ZIP_ENC_RAW) {
            fwrite(p,l,1,stdout);
        } else {
            printf("%lld", zipLoadInteger(p,encoding));
        }
        printf("\n");
        p += l;
    }
    printf("{end}\n\n");
}