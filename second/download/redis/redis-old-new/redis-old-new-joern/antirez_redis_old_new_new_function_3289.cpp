void setbitCommand(redisClient *c) {
    robj *o;
    size_t bitoffset;
    int on;

    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
        return;

    on = ((sds)c->argv[3]->ptr)[0] - '0';
    if (sdslen(c->argv[3]->ptr) != 1 || (on & ~1)) {
        addReplyError(c,"bit should be 0 or 1");
        return;
    }

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        sds value = sdssetbit(sdsempty(),bitoffset,on);
        o = createObject(REDIS_STRING,value);
        dbAdd(c->db,c->argv[1],o);
    } else {
        if (checkType(c,o,REDIS_STRING)) return;

        /* Create a copy when the object is shared or encoded. */
        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
            robj *decoded = getDecodedObject(o);
            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
            decrRefCount(decoded);
            dbReplace(c->db,c->argv[1],o);
        }

        o->ptr = sdssetbit(o->ptr,bitoffset,on);
    }
    touchWatchedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c,shared.cone);
}