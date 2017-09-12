}

static void hgetCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);

    if (o == NULL) {
        addReply(c,shared.nullbulk);
        return;
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }

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

static void hdelCommand(redisClient *c) {
    robj *o = lookupKeyWrite(c->db,c->argv[1]);

    if (o == NULL) {
        addReply(c,shared.czero);
        return;
    } else {
        int deleted = 0;

        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }

        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
            o->ptr = zipmapDel((unsigned char*) o->ptr,
                (unsigned char*) c->argv[2]->ptr,
                sdslen(c->argv[2]->ptr), &deleted);
        } else {
            deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
        }
        addReply(c,deleted ? shared.cone : shared.czero);
    }
}

static void hlenCommand(redisClient *c) {
    robj *o;
    unsigned long len;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    len = (o->encoding == REDIS_ENCODING_ZIPMAP) ?
