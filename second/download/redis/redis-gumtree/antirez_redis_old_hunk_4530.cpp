
static void dbsizeCommand(redisClient *c) {
    addReplySds(c,
        sdscatprintf(sdsempty(),":%lu\r\n",dictGetHashTableUsed(c->dict)));
}

static void lastsaveCommand(redisClient *c) {
