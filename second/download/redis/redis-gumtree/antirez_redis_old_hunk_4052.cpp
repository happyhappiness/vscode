    p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
    if (*p == ZIP_END) return zl;

    prevrawlen = zipDecodeLength(p,&prevrawlensize);
    len = zipDecodeLength(p+prevrawlensize,&lensize);
    headerlen = prevrawlensize+lensize;
    rawlen = headerlen+len;
    if (target) {
        encoding = ZIP_ENCODING(p+prevrawlensize);
        if (encoding == ZIP_ENC_RAW) {
            *target = sdsnewlen(p+headerlen,len);
        } else {
            value = zipLoadInteger(p+headerlen,encoding);
            *target = sdscatprintf(sdsempty(), "%lld", value);
        }
    }
