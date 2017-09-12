    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyLongLong(redisClient *c, long long ll) {
    char buf[128];
    size_t len;

    if (ll == 0) {
        addReply(c,shared.czero);
        return;
    } else if (ll == 1) {
        addReply(c,shared.cone);
        return;
    }
    len = snprintf(buf,sizeof(buf),":%lld\r\n",ll);
    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyUlong(redisClient *c, unsigned long ul) {
    char buf[128];
    size_t len;
