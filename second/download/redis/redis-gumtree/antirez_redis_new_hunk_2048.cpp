        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    /* Only support dense objects as destination. */
    if (hllSparseToDense(o) == REDIS_ERR) {
        addReplyError(c,"Invalid HLL object detected");
        return;
    }

    /* Write the resulting HLL to the destination HLL registers and
     * invalidate the cached value. */
    hdr = o->ptr;
