void zremrangebyscoreCommand(redisClient *c) {
    zrangespec range;
    long deleted;
    robj *o;
    zset *zs;

    /* Parse the range arguments. */
    zslParseRange(c->argv[2],c->argv[3],&range);

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_ZSET)) return;

    zs = o->ptr;
    deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
    if (deleted) touchWatchedKey(c->db,c->argv[1]);
    server.dirty += deleted;
    addReplyLongLong(c,deleted);
}