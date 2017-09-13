static void hincrbyCommand(redisClient *c) {
    int update = 0;
    long long value = 0, incr = 0;
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

    robj *o_incr = getDecodedObject(c->argv[3]);
    incr = strtoll(o_incr->ptr, NULL, 10);
    decrRefCount(o_incr);

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        unsigned char *zval;
        unsigned int zvlen;

        /* Find value if already present in hash */
        if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            &zval,&zvlen)) {
            /* strtoll needs the char* to have a trailing \0, but
             * the zipmap doesn't include them. */
            sds szval = sdsnewlen(zval, zvlen);
            value = strtoll(szval,NULL,10);
            sdsfree(szval);
        }

        value += incr;
        sds svalue = sdscatprintf(sdsempty(),"%lld",value);
        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            (unsigned char*)svalue,sdslen(svalue),&update);
        sdsfree(svalue);
        o->ptr = zm;

        /* Check if the zipmap needs to be converted
         * if this was not an update. */
        if (!update && zipmapLen(zm) > server.hash_max_zipmap_entries)
            convertToRealHash(o);
    } else {
        robj *hval;
        dictEntry *de;

        /* Find value if already present in hash */
        de = dictFind(o->ptr,c->argv[2]);
        if (de != NULL) {
            hval = dictGetEntryVal(de);
            if (hval->encoding == REDIS_ENCODING_RAW)
                value = strtoll(hval->ptr,NULL,10);
            else if (hval->encoding == REDIS_ENCODING_INT)
                value = (long)hval->ptr;
            else
                redisAssert(1 != 1);
        }

        value += incr;
        hval = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
        tryObjectEncoding(hval);
        incrRefCount(hval);

        if (dictReplace(o->ptr,c->argv[2],hval)) {
            incrRefCount(c->argv[2]);
        }
    }

    server.dirty++;
    addReplyLong(c, value);
}