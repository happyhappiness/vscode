
    /* Only support dense objects as destination. */
    if (hllSparseToDense(o) == REDIS_ERR) {
        addReplyError(c,"Invalid HLL object detected");
        return;
    }

