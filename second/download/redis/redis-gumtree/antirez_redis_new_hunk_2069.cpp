         * we would have a key as HLLADD creates it as a side effect. */
        addReply(c,shared.czero);
    } else {
        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;

        /* Check if the cached cardinality is valid. */
        registers = o->ptr;
