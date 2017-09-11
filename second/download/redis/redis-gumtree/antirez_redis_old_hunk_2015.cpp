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
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
        server.dirty++;
        /* Invalidate the cached cardinality. */
        registers[REDIS_HLL_SIZE-9] |= (1<<7);
    }
    addReply(c, updated ? shared.cone : shared.czero);
}

/* PFCOUNT var -> approximated cardinality of set. */
void pfcountCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    uint8_t *registers;
    uint64_t card;

    if (o == NULL) {
        /* No key? Cardinality is zero since no element was added, otherwise
         * we would have a key as HLLADD creates it as a side effect. */
