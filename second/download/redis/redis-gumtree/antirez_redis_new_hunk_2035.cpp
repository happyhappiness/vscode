
        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == REDIS_ERR) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
            conv = 1;
