    }
}

/* ==================================== Hash ================================ */
static void hsetCommand(redisClient *c) {
    int update = 0;
    robj *o = lookupKeyWrite(c->db,c->argv[1]);

    if (o == NULL) {
        o = createHashObject();
        dictAdd(c->db->dict,c->argv[1],o);
        incrRefCount(c->argv[1]);
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;

        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            c->argv[3]->ptr,sdslen(c->argv[3]->ptr),&update);
    } else {
        if (dictAdd(o->ptr,c->argv[2],c->argv[3]) == DICT_OK) {
            incrRefCount(c->argv[2]);
        } else {
            update = 1;
        }
        incrRefCount(c->argv[3]);
    }
    server.dirty++;
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
}

static void hgetCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);

    if (o == NULL) {
        addReply(c,shared.nullbulk);
        return;
    } else {
        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
            unsigned char *zm = o->ptr;
            unsigned char *val;
            unsigned int vlen;

            if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr), &val,&vlen)) {
                addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
                addReplySds(c,sdsnewlen(val,vlen));
                addReply(c,shared.crlf);
                return;
            } else {
                addReply(c,shared.nullbulk);
                return;
            }
        } else {
            struct dictEntry *de;

            de = dictFind(o->ptr,c->argv[2]);
            if (de == NULL) {
                addReply(c,shared.nullbulk);
            } else {
                robj *e = dictGetEntryVal(de);

                addReplyBulkLen(c,e);
                addReply(c,e);
                addReply(c,shared.crlf);
            }
        }
    }
}

/* ========================= Non type-specific commands  ==================== */

static void flushdbCommand(redisClient *c) {
