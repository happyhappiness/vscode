static void zcardCommand(redisClient *c) {
    robj *o;
    zset *zs;
    
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.czero);
        return;
    } else {
        if (o->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            zs = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",zs->zsl->length));
        }
    }
}

static void zscoreCommand(redisClient *c) {
    robj *o;
    zset *zs;
    
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.nullbulk);
        return;
    } else {
        if (o->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            dictEntry *de;

            zs = o->ptr;
            de = dictFind(zs->dict,c->argv[2]);
            if (!de) {
                addReply(c,shared.nullbulk);
            } else {
                double *score = dictGetEntryVal(de);

                addReplyDouble(c,*score);
            }
        }
    }
}

static void zrankGenericCommand(redisClient *c, int reverse) {
    robj *o;
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.nullbulk);
        return;
    }
    if (o->type != REDIS_ZSET) {
        addReply(c,shared.wrongtypeerr);
    } else {
        zset *zs = o->ptr;
        zskiplist *zsl = zs->zsl;
        dictEntry *de;
        unsigned long rank;

        de = dictFind(zs->dict,c->argv[2]);
        if (!de) {
            addReply(c,shared.nullbulk);
            return;
        }

        double *score = dictGetEntryVal(de);
        rank = zslGetRank(zsl, *score, c->argv[2]);
        if (rank) {
            if (reverse) {
                addReplyLong(c, zsl->length - rank);
            } else {
                addReplyLong(c, rank-1);
            }
        } else {
            addReply(c,shared.nullbulk);
        }
    }
}

