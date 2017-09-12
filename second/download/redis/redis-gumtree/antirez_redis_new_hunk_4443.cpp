    }
}

static void zlenCommand(redisClient *c) {
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
            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",zs->zsl->length));
        }
    }
}

/* ========================= Non type-specific commands  ==================== */

static void flushdbCommand(redisClient *c) {
