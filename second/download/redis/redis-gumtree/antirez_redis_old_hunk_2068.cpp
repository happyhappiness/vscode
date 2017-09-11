        dbAdd(c->db,c->argv[1],o);
        updated++;
    } else {
        /* Key exists, check type */
        if (checkType(c,o,REDIS_STRING))
            return;

        /* If this is a string representing an HLL, the size should match
         * exactly. */
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "PFADD target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }
        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }
    /* Perform the low level ADD operation for every element. */
