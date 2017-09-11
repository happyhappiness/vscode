
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "HLLADD target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }
