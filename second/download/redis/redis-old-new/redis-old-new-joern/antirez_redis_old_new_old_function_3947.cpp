unsigned char *ziplistPop(unsigned char *zl, sds *value, int where) {
    unsigned int curlen = ZIPLIST_BYTES(zl), len, rlen;
    unsigned char *p;
    if (value) *value = NULL;

    /* Get pointer to element to remove */
    p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
    if (*p == ZIP_END) return zl;
    len = zipDecodeLength(p);
    if (value) *value = sdsnewlen(p+zipEncodeLength(NULL,len),len);

    /* Move list to front when popping from the head */
    rlen = zipRawEntryLength(p);
    if (where == ZIPLIST_HEAD) {
        memmove(p,p+rlen,curlen-ZIPLIST_HEADER_SIZE-len);
    }

    /* Resize and update length */
    zl = ziplistResize(zl,curlen-rlen);
    ZIPLIST_INCR_LENGTH(zl,-1);
    return zl;
}