
        /* Make sure that for small cardinalities we use sparse
         * encoding. */
        if (j == checkpoint && j < HLL_SPARSE_MAX/2) {
            hdr2 = o->ptr;
            if (hdr2->encoding != HLL_SPARSE) {
                addReplyError(c, "TESTFAILED sparse encoding not used");
