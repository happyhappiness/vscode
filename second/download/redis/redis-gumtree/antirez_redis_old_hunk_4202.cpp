    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
}

static void hgetCommand(redisClient *c) {
    robj *o;

