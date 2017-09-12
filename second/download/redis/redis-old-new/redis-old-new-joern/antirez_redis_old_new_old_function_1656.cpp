void pfaddCommand(redisClient *c) {
    robj *o = lookupKeyWrite(c->db,c->argv[1]);
    uint8_t *registers;
    int updated = 0, j;

    if (o == NULL) {
        /* Create the key with a string value of the exact length to
         * hold our HLL data structure. sdsnewlen() when NULL is passed
         * is guaranteed to return bytes initialized to zero. */
        o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
        dbAdd(c->db,c->argv[1],o);
        updated++;
    } else {
        /* Key exists, check type */
        if (checkType(c,o,REDIS_STRING))
            return;

        /* If this is a string representing an HLL, the size should match
         * exactly. */
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "HLLADD target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }
        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }
    /* Perform the low level ADD operation for every element. */
    registers = o->ptr;
    for (j = 2; j < c->argc; j++) {
        if (hllAdd(registers, (unsigned char*)c->argv[j]->ptr,
                sdslen(c->argv[j]->ptr)))
        {
            updated++;
        }
    }
    if (updated) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
        server.dirty++;
        /* Invalidate the cached cardinality. */
        registers[REDIS_HLL_SIZE-1] |= (1<<7);
    }
    addReply(c, updated ? shared.cone : shared.czero);
}