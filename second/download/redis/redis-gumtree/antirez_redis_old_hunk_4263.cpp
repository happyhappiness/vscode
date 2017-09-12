    addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",(unsigned long)totlen));
}

/* ========================= Type agnostic commands ========================= */

static void delCommand(redisClient *c) {
