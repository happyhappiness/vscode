    zlentry entry;

    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
    p = ziplistHead(zl);
    while(*p != ZIP_END) {
        entry = zipEntry(p);
        printf("{offset %ld, header %u, payload %u} ",p-zl,entry.headersize,entry.len);
