    zfree(src);
    zfree(len);
    zfree(objects);

    /* Store the computed value into the target key */
    if (maxlen) {
        o = createObject(REDIS_STRING,res);
        setKey(c->db,targetkey,o);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",targetkey,c->db->id);
        decrRefCount(o);
    } else if (dbDelete(c->db,targetkey)) {
        signalModifiedKey(c->db,targetkey);
        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",targetkey,c->db->id);
    }
    server.dirty++;
    addReplyLongLong(c,maxlen); /* Return the output string length in bytes. */
}

/* BITCOUNT key [start end] */
void bitcountCommand(redisClient *c) {
    robj *o;
    long start, end, strlen;
    unsigned char *p;
    char llbuf[32];

    /* Lookup, check for type, and return 0 for non existing keys. */
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_STRING)) return;

    /* Set the 'p' pointer to the string, that can be just a stack allocated
     * array if our string was integer encoded. */
    if (o->encoding == REDIS_ENCODING_INT) {
        p = (unsigned char*) llbuf;
        strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
    } else {
        p = (unsigned char*) o->ptr;
        strlen = sdslen(o->ptr);
    }

    /* Parse start/end range if any. */
    if (c->argc == 4) {
        if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
            return;
        if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
            return;
        /* Convert negative indexes */
        if (start < 0) start = strlen+start;
        if (end < 0) end = strlen+end;
        if (start < 0) start = 0;
        if (end < 0) end = 0;
