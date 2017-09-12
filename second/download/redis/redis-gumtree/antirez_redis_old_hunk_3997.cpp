    return __ziplistInsert(zl,p,s,slen);
}

unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
    zlentry entry;
    unsigned char *p;
    long long value;
    if (target) *target = NULL;

    /* Get pointer to element to remove */
    p = (where == ZIPLIST_HEAD) ? ZIPLIST_ENTRY_HEAD(zl) : ZIPLIST_ENTRY_TAIL(zl);
    if (*p == ZIP_END) return zl;

    entry = zipEntry(p);
    if (target) {
        if (entry.encoding == ZIP_ENC_RAW) {
            *target = sdsnewlen(p+entry.headersize,entry.len);
        } else {
            value = zipLoadInteger(p+entry.headersize,entry.encoding);
            *target = sdscatprintf(sdsempty(), "%lld", value);
        }
    }

    zl = __ziplistDelete(zl,p,1);
    return zl;
}

/* Returns an offset to use for iterating with ziplistNext. When the given
 * index is negative, the list is traversed back to front. When the list
 * doesn't contain an element at the provided index, NULL is returned. */
