        (unsigned long) strlen(buf),buf));
}

static void addReplyLong(redisClient *c, long l) {
    char buf[128];
    size_t len;

    len = snprintf(buf,sizeof(buf),":%ld\r\n",l);
    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len;

