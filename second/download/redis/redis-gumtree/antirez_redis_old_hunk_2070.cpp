        /* Check type and size. */
        robj *o = lookupKeyRead(c->db,c->argv[j]);
        if (o == NULL) continue; /* Assume empty HLL for non existing var. */
        if (checkType(c,o,REDIS_STRING))
            return;

        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "PFADD target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }

        /* Merge with this HLL with our 'max' HHL by setting max[i]
         * to MAX(max[i],hll[i]). */
