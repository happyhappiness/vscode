    p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
    if (*p == ZIP_END) return zl;

    entry = zipEntry(p);
    rawlen = entry.headersize+entry.len;
    if (target) {
        if (entry.encoding == ZIP_ENC_RAW) {
            *target = sdsnewlen(p+entry.headersize,entry.len);
        } else {
            value = zipLoadInteger(p+entry.headersize,entry.encoding);
            *target = sdscatprintf(sdsempty(), "%lld", value);
        }
    }
