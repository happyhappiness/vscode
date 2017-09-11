        /* Check type and size. */
        robj *o = lookupKeyRead(c->db,c->argv[j]);
        if (o == NULL) continue; /* Assume empty HLL for non existing var. */
        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;

        /* Merge with this HLL with our 'max' HHL by setting max[i]
         * to MAX(max[i],hll[i]). */
