
        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == REDIS_ERR) {
                addReplyError(c,"HLL sparse encoding is corrupted");
                return;
            }
            server.dirty++; /* Force propagation on encoding change. */
