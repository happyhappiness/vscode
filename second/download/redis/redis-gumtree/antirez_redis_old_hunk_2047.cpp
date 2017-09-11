        /* Merge with this HLL with our 'max' HHL by setting max[i]
         * to MAX(max[i],hll[i]). */
        hdr = o->ptr;
        for (i = 0; i < HLL_REGISTERS; i++) {
            HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
            if (val > max[i]) max[i] = val;
        }
    }

    /* Create / unshare the destination key's value if needed. */
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        /* Create the key with a string value of the exact length to
         * hold our HLL data structure. sdsnewlen() when NULL is passed
