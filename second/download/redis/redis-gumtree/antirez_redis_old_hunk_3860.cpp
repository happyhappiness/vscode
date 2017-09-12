    int j;

    if (c->flags & REDIS_MULTI) {
        addReplySds(c,sdsnew("-ERR WATCH inside MULTI is not allowed\r\n"));
        return;
    }
    for (j = 1; j < c->argc; j++)
