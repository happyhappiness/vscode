        (unsigned long) strlen(buf),buf));
}

static void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len;

