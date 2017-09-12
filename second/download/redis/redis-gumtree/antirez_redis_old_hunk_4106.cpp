        addReply(c,shared.cone);
        return;
    }
    len = snprintf(buf,sizeof(buf),":%lld\r\n",ll);
    addReplySds(c,sdsnewlen(buf,len));
}

static void addReplyUlong(redisClient *c, unsigned long ul) {
