        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    /* Write the resulting HLL to the destination HLL registers and
     * invalidate the cached value. */
    hdr = o->ptr;
