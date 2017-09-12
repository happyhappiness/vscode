    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyUlong(redisClient *c, unsigned long ul) {
    char buf[128];
    size_t len;

    len = snprintf(buf,sizeof(buf),":%lu\r\n",ul);
    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len;

