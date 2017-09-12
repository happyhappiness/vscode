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

static void zrangeGenericCommand(redisClient *c, int reverse) {
    robj *o;
    int start = atoi(c->argv[2]->ptr);
