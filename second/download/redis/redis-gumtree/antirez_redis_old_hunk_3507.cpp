    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != REDIS_OK)
        return;

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        /* Negative offset is always 0 for non-existing keys */
        if (offset < 0) offset = 0;

        /* Return 0 when setting nothing on a non-existing string */
        if (sdslen(value) == 0) {
            addReply(c,shared.czero);
