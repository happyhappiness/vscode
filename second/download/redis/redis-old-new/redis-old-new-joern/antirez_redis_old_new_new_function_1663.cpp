void pfcountCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    uint8_t *registers;
    uint64_t card;

    if (o == NULL) {
        /* No key? Cardinality is zero since no element was added, otherwise
         * we would have a key as HLLADD creates it as a side effect. */
        addReply(c,shared.czero);
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

        /* Check if the cached cardinality is valid. */
        registers = o->ptr;
        if ((registers[REDIS_HLL_SIZE-1] & (1<<7)) == 0) {
            /* Just return the cached value. */
            card = (uint64_t)registers[REDIS_HLL_SIZE-8];
            card |= (uint64_t)registers[REDIS_HLL_SIZE-7] << 8;
            card |= (uint64_t)registers[REDIS_HLL_SIZE-6] << 16;
            card |= (uint64_t)registers[REDIS_HLL_SIZE-5] << 24;
            card |= (uint64_t)registers[REDIS_HLL_SIZE-4] << 32;
            card |= (uint64_t)registers[REDIS_HLL_SIZE-3] << 40;
            card |= (uint64_t)registers[REDIS_HLL_SIZE-2] << 48;
            card |= (uint64_t)registers[REDIS_HLL_SIZE-1] << 56;
        } else {
            /* Recompute it and update the cached value. */
            card = hllCount(registers);
            registers[REDIS_HLL_SIZE-8] = card & 0xff;
            registers[REDIS_HLL_SIZE-7] = (card >> 8) & 0xff;
            registers[REDIS_HLL_SIZE-6] = (card >> 16) & 0xff;
            registers[REDIS_HLL_SIZE-5] = (card >> 24) & 0xff;
            registers[REDIS_HLL_SIZE-4] = (card >> 32) & 0xff;
            registers[REDIS_HLL_SIZE-3] = (card >> 40) & 0xff;
            registers[REDIS_HLL_SIZE-2] = (card >> 48) & 0xff;
            registers[REDIS_HLL_SIZE-1] = (card >> 56) & 0xff;
            /* This is not considered a read-only command even if the
             * data structure is not modified, since the cached value
             * may be modified and given that the HLL is a Redis string
             * we need to propagate the change. */
            signalModifiedKey(c->db,c->argv[1]);
            server.dirty++;
        }
        addReplyLongLong(c,card);
    }
}