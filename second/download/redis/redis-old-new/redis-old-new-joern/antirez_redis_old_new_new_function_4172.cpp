static void zremrangebyscoreCommand(redisClient *c) {
    double min = strtod(c->argv[2]->ptr,NULL);
    double max = strtod(c->argv[3]->ptr,NULL);
    long deleted;
    robj *zsetobj;
    zset *zs;

    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,zsetobj,REDIS_ZSET)) return;

    zs = zsetobj->ptr;
    deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
    server.dirty += deleted;
    addReplyLong(c,deleted);
}