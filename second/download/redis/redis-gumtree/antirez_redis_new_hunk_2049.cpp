
        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == REDIS_ERR) {
                addReplyError(c,"Invalid HLL object detected");
                return;
            }
            server.dirty++; /* Force propagation on encoding change. */
