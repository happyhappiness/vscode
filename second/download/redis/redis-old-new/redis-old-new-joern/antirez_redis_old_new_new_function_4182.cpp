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