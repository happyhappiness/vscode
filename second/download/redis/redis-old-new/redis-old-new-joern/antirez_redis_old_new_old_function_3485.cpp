void zremrangebyscoreCommand(redisClient *c) {
    double min;
    double max;
    long deleted;
    robj *zsetobj;
    zset *zs;

    if ((getDoubleFromObjectOrReply(c, c->argv[2], &min, NULL) != REDIS_OK) ||
        (getDoubleFromObjectOrReply(c, c->argv[3], &max, NULL) != REDIS_OK)) return;

    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,zsetobj,REDIS_ZSET)) return;

    zs = zsetobj->ptr;
    deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
    if (deleted) touchWatchedKey(c->db,c->argv[1]);
    server.dirty += deleted;
    addReplyLongLong(c,deleted);
}