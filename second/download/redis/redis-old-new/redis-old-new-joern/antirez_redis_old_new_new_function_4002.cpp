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
    buf[0] = ':';
    len = ll2string(buf+1,sizeof(buf)-1,ll);
    buf[len+1] = '\r';
    buf[len+2] = '\n';
    addReplySds(c,sdsnewlen(buf,len+3));
}