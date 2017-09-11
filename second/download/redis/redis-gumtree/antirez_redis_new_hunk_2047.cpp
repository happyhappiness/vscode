        /* Merge with this HLL with our 'max' HHL by setting max[i]
         * to MAX(max[i],hll[i]). */
        hdr = o->ptr;
        if (hdr->encoding == HLL_DENSE) {
            uint8_t val;

            for (i = 0; i < HLL_REGISTERS; i++) {
                HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
                if (val > max[i]) max[i] = val;
            }
        } else {
            uint8_t *p = o->ptr, *end = p + sdslen(o->ptr);
            long runlen, regval;

            p += HLL_HDR_SIZE;
            i = 0;
            while(p < end) {
                if (HLL_SPARSE_IS_ZERO(p)) {
                    runlen = HLL_SPARSE_ZERO_LEN(p);
                    i += runlen;
                    p++;
                } else if (HLL_SPARSE_IS_XZERO(p)) {
                    runlen = HLL_SPARSE_XZERO_LEN(p);
                    i += runlen;
                    p += 2;
                } else {
                    runlen = HLL_SPARSE_VAL_LEN(p);
                    regval = HLL_SPARSE_VAL_VALUE(p);
                    while(runlen--) {
                        if (regval > max[i]) max[i] = regval;
                        i++;
                    }
                    p++;
                }
            }
            if (i != HLL_REGISTERS) {
                addReplyError(c,"Invalid HLL object detected");
                return;
            }
        }
    }

    /* Create / unshare the destination key's value if needed. */
    robj *o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        /* Create the key with a string value of the exact length to
         * hold our HLL data structure. sdsnewlen() when NULL is passed
