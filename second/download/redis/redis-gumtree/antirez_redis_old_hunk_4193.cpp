    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
}

static void hincrbyCommand(redisClient *c) {
    long long value = 0, incr = 0;
    robj *o = lookupKeyWrite(c->db,c->argv[1]);
