    decrRefCount(o);
}

static void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len;

