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
