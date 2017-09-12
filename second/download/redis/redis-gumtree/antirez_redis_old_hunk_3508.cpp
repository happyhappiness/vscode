}

void appendCommand(redisClient *c) {
    int retval;
    size_t totlen;
    robj *o, *append;

    o = lookupKeyWrite(c->db,c->argv[1]);
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    if (o == NULL) {
        /* Create the key */
        retval = dbAdd(c->db,c->argv[1],c->argv[2]);
        incrRefCount(c->argv[2]);
        totlen = stringObjectLen(c->argv[2]);
    } else {
        if (o->type != REDIS_STRING) {
            addReply(c,shared.wrongtypeerr);
            return;
        }

        append = getDecodedObject(c->argv[2]);
        if (o->encoding == REDIS_ENCODING_RAW &&
            (sdslen(o->ptr) + sdslen(append->ptr)) > 512*1024*1024)
        {
            addReplyError(c,"string exceeds maximum allowed size (512MB)");
            decrRefCount(append);
            return;
        }

        /* If the object is shared or encoded, we have to make a copy */
        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
