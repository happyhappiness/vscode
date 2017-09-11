
    /* Only support dense objects as destination. */
    if (hllSparseToDense(o) == REDIS_ERR) {
        addReplyError(c,invalid_hll_err);
        return;
    }

