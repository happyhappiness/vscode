    if (!strcasecmp(cmd,"getreg")) {
        if (c->argc != 3) goto arityerr;

        if (hllSparseToDense(o) == REDIS_ERR) {
            addReplyError(c,"HLL sparse encoding is corrupted");
            return;
        }

        hdr = o->ptr;
        addReplyMultiBulkLen(c,HLL_REGISTERS);
        for (j = 0; j < HLL_REGISTERS; j++) {
            uint8_t val;

