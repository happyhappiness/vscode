    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len;

