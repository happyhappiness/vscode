static void sismemberCommand(redisClient *c) {
    robj *set;

    set = lookupKeyRead(c->db,c->argv[1]);
    if (set == NULL) {
        addReply(c,shared.czero);
    } else {
        if (set->type != REDIS_SET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
        if (dictFind(set->ptr,c->argv[2]))
            addReply(c,shared.cone);
        else
            addReply(c,shared.czero);
    }
}

static void scardCommand(redisClient *c) {
    robj *o;
    dict *s;
    
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.czero);
        return;
    } else {
        if (o->type != REDIS_SET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            s = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
                dictSize(s)));
        }
    }
}

static void spopCommand(redisClient *c) {
    robj *set;
    dictEntry *de;

    set = lookupKeyWrite(c->db,c->argv[1]);
    if (set == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        if (set->type != REDIS_SET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
        de = dictGetRandomKey(set->ptr);
        if (de == NULL) {
            addReply(c,shared.nullbulk);
        } else {
            robj *ele = dictGetEntryKey(de);

            addReplyBulkLen(c,ele);
            addReply(c,ele);
            addReply(c,shared.crlf);
            dictDelete(set->ptr,ele);
            if (htNeedsResize(set->ptr)) dictResize(set->ptr);
            server.dirty++;
        }
    }
}

static void srandmemberCommand(redisClient *c) {
    robj *set;
    dictEntry *de;

    set = lookupKeyRead(c->db,c->argv[1]);
    if (set == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        if (set->type != REDIS_SET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
        de = dictGetRandomKey(set->ptr);
        if (de == NULL) {
            addReply(c,shared.nullbulk);
        } else {
            robj *ele = dictGetEntryKey(de);

            addReplyBulkLen(c,ele);
            addReply(c,ele);
            addReply(c,shared.crlf);
        }
    }
}

