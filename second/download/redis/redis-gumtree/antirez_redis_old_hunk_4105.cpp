        (unsigned long) strlen(buf),buf));
}

static void addReplyLong(redisClient *c, long l) {
    char buf[128];
    size_t len;

    if (l == 0) {
        addReply(c,shared.czero);
        return;
    } else if (l == 1) {
        addReply(c,shared.cone);
        return;
    }
    len = snprintf(buf,sizeof(buf),":%ld\r\n",l);
    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyLongLong(redisClient *c, long long ll) {
    char buf[128];
    size_t len;
