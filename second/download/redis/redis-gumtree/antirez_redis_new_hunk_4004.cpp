}

/* Write a long value in bulk format $<count>\r\n<payload>\r\n */
static int fwriteBulkLongLong(FILE *fp, long long l) {
    char bbuf[128], lbuf[128];
    unsigned int blen, llen;
    llen = ll2string(lbuf,32,l);
    blen = snprintf(bbuf,sizeof(bbuf),"$%u\r\n%s\r\n",llen,lbuf);
    if (fwrite(bbuf,blen,1,fp) == 0) return 0;
    return 1;
}

/* Delegate writing an object to writing a bulk string or bulk long long. */
static int fwriteBulkObject(FILE *fp, robj *obj) {
    /* Avoid using getDecodedObject to help copy-on-write (we are often
     * in a child process when this function is called). */
    if (obj->encoding == REDIS_ENCODING_INT) {
        return fwriteBulkLongLong(fp,(long)obj->ptr);
    } else if (obj->encoding == REDIS_ENCODING_RAW) {
        return fwriteBulkString(fp,obj->ptr,sdslen(obj->ptr));
    } else {
        redisPanic("Unknown string encoding");
    }
}

/* Write a sequence of commands able to fully rebuild the dataset into
 * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
static int rewriteAppendOnlyFile(char *filename) {
