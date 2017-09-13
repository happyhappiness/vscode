static void hmgetCommand(redisClient *c) {
    int i;

    robj *o = lookupKeyRead(c->db, c->argv[1]);
    if (o == NULL) {
        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
        for (i = 2; i < c->argc; i++) {
            addReply(c,shared.nullbulk);
        }
        return;
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }

    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        unsigned char *v;
        unsigned int vlen;
        robj *field;

        for (i = 2; i < c->argc; i++) {
            field = getDecodedObject(c->argv[i]);
            if (zipmapGet(zm,field->ptr,sdslen(field->ptr),&v,&vlen)) {
                addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
                addReplySds(c,sdsnewlen(v,vlen));
                addReply(c,shared.crlf);
            } else {
                addReply(c,shared.nullbulk);
            }
            decrRefCount(field);
        }
    } else {
        dictEntry *de;

        for (i = 2; i < c->argc; i++) {
            de = dictFind(o->ptr,c->argv[i]);
            if (de != NULL) {
                addReplyBulk(c,(robj*)dictGetEntryVal(de));
            } else {
                addReply(c,shared.nullbulk);
            }
        }
    }
}