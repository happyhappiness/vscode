
        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == REDIS_ERR) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
            server.dirty++; /* Force propagation on encoding change. */
