static void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len, intlen;
    char buf[128];

    if (obj->encoding == REDIS_ENCODING_RAW) {
        len = sdslen(obj->ptr);
    } else {
        long n = (long)obj->ptr;

        /* Compute how many bytes will take this integer as a radix 10 string */
        len = 1;
        if (n < 0) {
            len++;
            n = -n;
        }
        while((n = n/10) != 0) {
            len++;
        }
    }
    buf[0] = '$';
    intlen = ll2string(buf+1,sizeof(buf)-1,(long long)len);
    buf[intlen+1] = '\r';
    buf[intlen+2] = '\n';
    addReplySds(c,sdsnewlen(buf,intlen+3));
}