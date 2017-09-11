cleanup:
    sdsfree(bitcounters);
}

/* PFGETREG
 * Return the registers values of the specified HLL. */
void pfgetregCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    uint8_t *registers;
    int j;

    if (o == NULL) {
        addReplyError(c,"The specified key does not exist");
        return;
    } else {
        /* Key exists, check type */
        if (checkType(c,o,REDIS_STRING))
            return;

        /* If this is a string representing an HLL, the size should match
         * exactly. */
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "PFCOUNT target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }

        registers = o->ptr;
        addReplyMultiBulkLen(c,REDIS_HLL_REGISTERS);
        for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
            uint8_t val;

            HLL_GET_REGISTER(val,registers,j);
            addReplyLongLong(c,val);
        }
    }
}
