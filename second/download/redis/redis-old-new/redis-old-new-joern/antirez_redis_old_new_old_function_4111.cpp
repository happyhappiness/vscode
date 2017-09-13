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
    /* We want to convert the zipmap into an hash table right now if the
     * entry to be added is too big. Note that we check if the object
     * is integer encoded before to try fetching the length in the test below.
     * This is because integers are small, but currently stringObjectLen()
     * performs a slow conversion: not worth it. */
    if (o->encoding == REDIS_ENCODING_ZIPMAP &&
        ((c->argv[2]->encoding == REDIS_ENCODING_RAW &&
          sdslen(c->argv[2]->ptr) > server.hash_max_zipmap_value) ||
         (c->argv[3]->encoding == REDIS_ENCODING_RAW &&
          sdslen(c->argv[3]->ptr) > server.hash_max_zipmap_value)))
    {
        convertToRealHash(o);
    }

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        robj *valobj = getDecodedObject(c->argv[3]);

        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            valobj->ptr,sdslen(valobj->ptr),&update);
        decrRefCount(valobj);
        o->ptr = zm;

        /* And here there is the second check for hash conversion. */
        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
            convertToRealHash(o);
    } else {
        c->argv[2] = tryObjectEncoding(c->argv[2]);
        /* note that c->argv[3] is already encoded, as the latest arg
         * of a bulk command is always integer encoded if possible. */
        if (dictReplace(o->ptr,c->argv[2],c->argv[3])) {
            incrRefCount(c->argv[2]);
        } else {
            update = 1;
        }
        incrRefCount(c->argv[3]);
    }
    server.dirty++;
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
}