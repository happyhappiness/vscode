
void ziplistRepr(unsigned char *zl) {
    unsigned char *p;
    zlentry entry;

    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
    p = ZIPLIST_ENTRY_HEAD(zl);
    while(*p != ZIP_END) {
        entry = zipEntry(p);
        printf("{offset %ld, header %u, payload %u} ",p-zl,entry.headersize,entry.len);
        p += entry.headersize;
        if (ZIP_IS_STR(entry.encoding)) {
            fwrite(p,entry.len,1,stdout);
        } else {
            printf("%lld", (long long) zipLoadInteger(p,entry.encoding));
        }
        printf("\n");
        p += entry.len;
    }
    printf("{end}\n\n");
}
