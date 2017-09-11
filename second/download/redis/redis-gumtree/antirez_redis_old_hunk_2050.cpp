    if (!strcasecmp(cmd,"getreg")) {
        if (c->argc != 3) goto arityerr;

        if (hllSparseToDense(o) == REDIS_ERR) {
            addReplyError(c,"HLL sparse encoding is corrupted");
            return;
        }

        hdr = o->ptr;
