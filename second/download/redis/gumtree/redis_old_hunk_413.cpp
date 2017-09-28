        pos++;
        one >>= 1;
    }

    /* If we reached this point, there is a bug in the algorithm, since
     * the case of no match is handled as a special case before. */
    redisPanic("End of redisBitpos() reached.");
    return 0; /* Just to avoid warnings. */
}

/* -----------------------------------------------------------------------------
 * Bits related string commands: GETBIT, SETBIT, BITCOUNT, BITOP.
 * -------------------------------------------------------------------------- */

#define BITOP_AND   0
#define BITOP_OR    1
#define BITOP_XOR   2
#define BITOP_NOT   3

/* SETBIT key offset bitvalue */
void setbitCommand(redisClient *c) {
    robj *o;
    char *err = "bit is not an integer or out of range";
    size_t bitoffset;
    int byte, bit;
    int byteval, bitval;
    long on;

    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
        return;

    if (getLongFromObjectOrReply(c,c->argv[3],&on,err) != REDIS_OK)
        return;

    /* Bits can only be set or cleared... */
    if (on & ~1) {
        addReplyError(c,err);
        return;
    }

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        o = createObject(REDIS_STRING,sdsempty());
        dbAdd(c->db,c->argv[1],o);
    } else {
        if (checkType(c,o,REDIS_STRING)) return;
        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    /* Grow sds value to the right length if necessary */
    byte = bitoffset >> 3;
    o->ptr = sdsgrowzero(o->ptr,byte+1);

    /* Get current values */
    byteval = ((uint8_t*)o->ptr)[byte];
    bit = 7 - (bitoffset & 0x7);
    bitval = byteval & (1 << bit);

    /* Update byte with new bit value and return original value */
    byteval &= ~(1 << bit);
    byteval |= ((on & 0x1) << bit);
    ((uint8_t*)o->ptr)[byte] = byteval;
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
    server.dirty++;
    addReply(c, bitval ? shared.cone : shared.czero);
}

/* GETBIT key offset */
void getbitCommand(redisClient *c) {
    robj *o;
    char llbuf[32];
    size_t bitoffset;
    size_t byte, bit;
    size_t bitval = 0;

    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
        return;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_STRING)) return;

    byte = bitoffset >> 3;
    bit = 7 - (bitoffset & 0x7);
    if (sdsEncodedObject(o)) {
        if (byte < sdslen(o->ptr))
            bitval = ((uint8_t*)o->ptr)[byte] & (1 << bit);
