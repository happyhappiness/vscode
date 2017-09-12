}

static void hgetCommand(redisClient *c) {
    robj *o;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

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

            addReplyBulk(c,e);
        }
    }
}

static void hdelCommand(redisClient *c) {
    robj *o;
    int deleted = 0;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        o->ptr = zipmapDel((unsigned char*) o->ptr,
            (unsigned char*) c->argv[2]->ptr,
            sdslen(c->argv[2]->ptr), &deleted);
    } else {
        deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
    }
    addReply(c,deleted ? shared.cone : shared.czero);
}

static void hlenCommand(redisClient *c) {
    robj *o;
    unsigned long len;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    len = (o->encoding == REDIS_ENCODING_ZIPMAP) ?
