        if (c->argc != 3) goto arityerr;

        addReplyMultiBulkLen(c,HLL_REGISTERS);
        hllSparseToDense(o);
        for (j = 0; j < HLL_REGISTERS; j++) {
            uint8_t val;

