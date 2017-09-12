
unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
    unsigned int curlen = ZIPLIST_BYTES(zl), rawlen;
    unsigned int len, lensize;
    unsigned char *p;
    long long value;
    if (target) *target = NULL;

    /* Get pointer to element to remove */
    p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
    if (*p == ZIP_END) return zl;
    len = zipDecodeLength(p,&lensize);
    if (target) {
        if (ZIP_ENCODING(p) == ZIP_ENC_RAW) {
            *target = sdsnewlen(p+lensize,len);
        } else {
            value = zipLoadInteger(p+lensize,ZIP_ENCODING(p));
            *target = sdscatprintf(sdsempty(), "%lld", value);
        }
    }

    /* Move list to front when popping from the head */
    rawlen = lensize+len;
    if (where == ZIPLIST_HEAD) {
        memmove(p,p+rawlen,curlen-ZIPLIST_HEADER_SIZE-len);
    }

    /* Resize and update length */
    zl = ziplistResize(zl,curlen-rawlen);
    ZIPLIST_INCR_LENGTH(zl,-1);
    return zl;
}
