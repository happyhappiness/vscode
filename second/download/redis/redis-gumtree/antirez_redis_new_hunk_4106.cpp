        addReply(c,shared.cone);
        return;
    }
    buf[0] = ':';
    len = ll2string(buf+1,sizeof(buf)-1,ll);
    buf[len+1] = '\r';
    buf[len+2] = '\n';
    addReplySds(c,sdsnewlen(buf,len+3));
}

static void addReplyUlong(redisClient *c, unsigned long ul) {
