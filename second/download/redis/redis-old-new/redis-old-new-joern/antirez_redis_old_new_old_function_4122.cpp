static void hgetCommand(redisClient *c) {
    robj *o;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        unsigned char *val;
        unsigned int vlen;
        robj *field;

        field = getDecodedObject(c->argv[2]);
        if (zipmapGet(zm,field->ptr,sdslen(field->ptr), &val,&vlen)) {
            addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
            addReplySds(c,sdsnewlen(val,vlen));
            addReply(c,shared.crlf);
            decrRefCount(field);
            return;
        } else {
            addReply(c,shared.nullbulk);
            decrRefCount(field);
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