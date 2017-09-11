         * exactly. */
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "HLLCOUNT target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }
