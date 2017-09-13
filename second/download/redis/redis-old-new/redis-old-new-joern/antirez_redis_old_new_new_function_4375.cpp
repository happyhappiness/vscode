static void zremrangebyscoreCommand(redisClient *c) {
    double min = strtod(c->argv[2]->ptr,NULL);
    double max = strtod(c->argv[3]->ptr,NULL);
    robj *zsetobj;
    zset *zs;

    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
    if (zsetobj == NULL) {
        addReply(c,shared.czero);
    } else {
        long deleted;

        if (zsetobj->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
        zs = zsetobj->ptr;
        deleted = zslDeleteRange(zs->zsl,min,max,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        server.dirty += deleted;
        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));
    }
}