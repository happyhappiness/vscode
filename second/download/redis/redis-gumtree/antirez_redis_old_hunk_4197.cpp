    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyUlong(redisClient *c, unsigned long ul) {
    char buf[128];
    size_t len;
