    decrRefCount(o);
}

static void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len;

    if (obj->encoding == REDIS_ENCODING_RAW) {
        len = sdslen(obj->ptr);
    } else {
        long n = (long)obj->ptr;

        len = 1;
        if (n < 0) {
            len++;
            n = -n;
        }
        while((n = n/10) != 0) {
            len++;
        }
    }
    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",len));
}

static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    int cport, cfd;
    char cip[128];
