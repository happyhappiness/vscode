void ziplistRepr(unsigned char *zl) {
    unsigned char *p, encoding;
    unsigned int prevrawlensize, prevrawlen, lensize, len;

    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
    p = ziplistHead(zl);
    while(*p != ZIP_END) {
        prevrawlen = zipDecodeLength(p,&prevrawlensize);
        len = zipDecodeLength(p+prevrawlensize,&lensize);
        printf("{offset %ld, header %u, payload %u} ",p-zl,prevrawlensize+lensize,len);
        encoding = ZIP_ENCODING(p+prevrawlensize);
        p += prevrawlensize+lensize;
        if (encoding == ZIP_ENC_RAW) {
            fwrite(p,len,1,stdout);
        } else {
            printf("%lld", zipLoadInteger(p,encoding));
        }
        printf("\n");
        p += len;
    }
    printf("{end}\n\n");
}