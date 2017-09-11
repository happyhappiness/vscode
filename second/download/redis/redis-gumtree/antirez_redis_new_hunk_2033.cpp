
    /* Only support dense objects as destination. */
    if (hllSparseToDense(o) == REDIS_ERR) {
        addReplySds(c,sdsnew(invalid_hll_err));
        return;
    }

