addReplyErrorFormat(c,
                "PFADD target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);