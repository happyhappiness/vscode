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
