static void zremCommand(redisClient *c) {
    robj *zsetobj;
    zset *zs;

    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
    if (zsetobj == NULL) {
        addReply(c,shared.czero);
    } else {
        dictEntry *de;
        double *oldscore;
        int deleted;

        if (zsetobj->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
        zs = zsetobj->ptr;
        de = dictFind(zs->dict,c->argv[2]);
        if (de == NULL) {
            addReply(c,shared.czero);
            return;
        }
        /* Delete from the skiplist */
        oldscore = dictGetEntryVal(de);
        deleted = zslDelete(zs->zsl,*oldscore,c->argv[2]);
        redisAssert(deleted != 0);

        /* Delete from the hash table */
        dictDelete(zs->dict,c->argv[2]);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        server.dirty++;
        addReply(c,shared.cone);
    }
}

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
        deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        server.dirty += deleted;
        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));
    }
}

static void zremrangebyrankCommand(redisClient *c) {
    int start = atoi(c->argv[2]->ptr);
    int end = atoi(c->argv[3]->ptr);
    robj *zsetobj;
    zset *zs;

    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
    if (zsetobj == NULL) {
        addReply(c,shared.czero);
    } else {
        if (zsetobj->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }

        zs = zsetobj->ptr;
        int llen = zs->zsl->length;
        long deleted;

        /* convert negative indexes */
        if (start < 0) start = llen+start;
        if (end < 0) end = llen+end;
        if (start < 0) start = 0;
        if (end < 0) end = 0;

        /* indexes sanity checks */
        if (start > end || start >= llen) {
            addReply(c,shared.czero);
            return;
        }
        if (end >= llen) end = llen-1;

        /* increment start and end because zsl*Rank functions
         * use 1-based rank */
        deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        server.dirty += deleted;
        addReplyLong(c, deleted);
    }
}

typedef struct {
