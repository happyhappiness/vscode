
unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
    unsigned int curlen = ZIPLIST_BYTES(zl), rawlen;
    unsigned int prevrawlensize, prevrawlen, lensize, len, headerlen;
    int nextdiff = 0;
    unsigned char encoding;
    unsigned char *p;
    long long value;
    if (target) *target = NULL;

    /* Get pointer to element to remove */
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

    if (where == ZIPLIST_HEAD) {
        /* The next entry will now be the head of the list */
        if (p[rawlen] != ZIP_END) {
            /* Tricky: storing the length of the previous entry in the next
             * entry (this previous length is always 0 when popping from the
             * head), might reduce the number of bytes needed.
             *
             * In this special case (new length is 0), we know that the
             * byte difference to store is always <= 0, which means that
             * we always have space to store it. */
            nextdiff = zipPrevLenByteDiff(p+rawlen,0);
            zipEncodeLength(p+rawlen-nextdiff,ZIP_ENC_RAW,0);
        }
        /* Move list to the front */
        memmove(p,p+rawlen-nextdiff,curlen-ZIPLIST_HEADER_SIZE-rawlen+nextdiff);

        /* Subtract the gained space from the tail offset */
        ZIPLIST_TAIL_OFFSET(zl) -= rawlen+nextdiff;
    } else {
        /* Subtract the length of the previous element from the tail offset. */
        ZIPLIST_TAIL_OFFSET(zl) -= prevrawlen;
    }

    /* Resize and update length */
    zl = ziplistResize(zl,curlen-rawlen+nextdiff);
    ZIPLIST_INCR_LENGTH(zl,-1);
    return zl;
}
