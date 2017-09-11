    addReply(c, updated ? shared.cone : shared.czero);
}

/* HLLCOUNT var -> approximated cardinality of set. */
void hllCountCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    uint8_t *registers;

    if (o == NULL) {
        /* No key? Cardinality is zero since no element was added, otherwise
         * we would have a key as HHLADD creates it as a side effect. */
        addReply(c,shared.czero);
    } else {
        /* Key exists, check type */
        if (checkType(c,o,REDIS_STRING))
            return;

        /* If this is a string representing an HLL, the size should match
         * exactly. */
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "HLLCOUNT target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }
        registers = o->ptr;
        addReplyLongLong(c,hllCount(registers));
    }
}


/* This command performs a self-test of the HLL registers implementation.
 * Something that is not easy to test from within the outside.
 *
