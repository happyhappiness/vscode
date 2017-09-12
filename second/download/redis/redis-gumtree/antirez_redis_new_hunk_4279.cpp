    incrDecrCommand(c,-incr);
}

static void appendCommand(redisClient *c) {
    int retval;
    size_t totlen;
    robj *o;

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        /* Create the key */
        retval = dictAdd(c->db->dict,c->argv[1],c->argv[2]);
        incrRefCount(c->argv[1]);
        incrRefCount(c->argv[2]);
        totlen = stringObjectLen(c->argv[2]);
    } else {
        dictEntry *de;
       
        de = dictFind(c->db->dict,c->argv[1]);
        assert(de != NULL);

        o = dictGetEntryVal(de);
        if (o->type != REDIS_STRING) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
        /* If the object is specially encoded or shared we have to make
         * a copy */
        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
            robj *decoded = getDecodedObject(o);

            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
            decrRefCount(decoded);
            dictReplace(c->db->dict,c->argv[1],o);
        }
        /* APPEND! */
        if (c->argv[2]->encoding == REDIS_ENCODING_RAW) {
            o->ptr = sdscatlen(o->ptr,
                c->argv[2]->ptr, sdslen(c->argv[2]->ptr));
        } else {
            o->ptr = sdscatprintf(o->ptr, "%ld",
                (unsigned long) c->argv[2]->ptr);
        }
        totlen = sdslen(o->ptr);
    }
    server.dirty++;
    addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",(unsigned long)totlen));
}

/* ========================= Type agnostic commands ========================= */

static void delCommand(redisClient *c) {
