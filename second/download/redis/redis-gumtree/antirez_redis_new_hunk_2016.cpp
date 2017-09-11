        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    /* Only support dense objects as destination. */
    if (hllSparseToDense(o) == REDIS_ERR) {
        addReplySds(c,sdsnew(invalid_hll_err));
        return;
    }

    /* Write the resulting HLL to the destination HLL registers and
     * invalidate the cached value. */
    hdr = o->ptr;
    for (j = 0; j < HLL_REGISTERS; j++) {
        HLL_DENSE_SET_REGISTER(hdr->registers,j,max[j]);
    }
    HLL_INVALIDATE_CACHE(hdr);

    signalModifiedKey(c->db,c->argv[1]);
    /* We generate an PFADD event for PFMERGE for semantical simplicity
     * since in theory this is a mass-add of elements. */
    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
    server.dirty++;
