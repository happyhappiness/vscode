static void zcardCommand(redisClient *c) {
    robj *o;
    zset *zs;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_ZSET)) return;

    zs = o->ptr;
    addReplyUlong(c,zs->zsl->length);
}