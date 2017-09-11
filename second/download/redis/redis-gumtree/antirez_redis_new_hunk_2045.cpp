
        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == REDIS_ERR) {
                addReplyError(c,invalid_hll_err);
                return;
            }
            server.dirty++; /* Force propagation on encoding change. */
