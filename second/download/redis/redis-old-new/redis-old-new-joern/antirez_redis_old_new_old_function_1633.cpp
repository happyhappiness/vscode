void pfmergeCommand(redisClient *c) {
    uint8_t max[HLL_REGISTERS];
    struct hllhdr *hdr;
    int j, i;

    /* Compute an HLL with M[i] = MAX(M[i]_j).
     * We we the maximum into the max array of registers. We'll write
     * it to the target variable later. */
    memset(max,0,sizeof(max));
    for (j = 1; j < c->argc; j++) {
        uint8_t val;

        /* Check type and size. */
        robj *o = lookupKeyRead(c->db,c->argv[j]);
        if (o == NULL) continue; /* Assume empty HLL for non existing var. */
        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;

        /* Merge with this HLL with our 'max' HHL by setting max[i]
         * to MAX(max[i],hll[i]). */
        hdr = o->ptr;
        for (i = 0; i < HLL_REGISTERS; i++) {
            HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
            if (val > max[i]) max[i] = val;
        }
    }

    /* Create / unshare the destination key's value if needed. */
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        /* Create the key with a string value of the exact length to
         * hold our HLL data structure. sdsnewlen() when NULL is passed
         * is guaranteed to return bytes initialized to zero. */
        o = createHLLObject();
        dbAdd(c->db,c->argv[1],o);
    } else {
        /* If key exists we are sure it's of the right type/size
         * since we checked when merging the different HLLs, so we
         * don't check again. */
        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    /* Write the resulting HLL to the destination HLL registers and
     * invalidate the cached value. */
    hdr = o->ptr;
    for (j = 0; j < HLL_REGISTERS; j++) {
        HLL_DENSE_SET_REGISTER(hdr->registers,j,max[j]);
    }
    HLL_INVALIDATE_CACHE(hdr);

    signalModifiedKey(c->db,c->argv[1]);
    /* We generate an HLLADD event for HLLMERGE for semantical simplicity
     * since in theory this is a mass-add of elements. */
    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
    server.dirty++;
    addReply(c,shared.ok);
}