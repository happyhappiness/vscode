        if (getLongFromObjectOrReply(c, expire, &seconds, NULL) != REDIS_OK)
            return;
        if (seconds <= 0) {
            addReplySds(c,sdsnew("-ERR invalid expire time in SETEX\r\n"));
            return;
        }
    }

    if (nx) deleteIfVolatile(c->db,key);
    retval = dbAdd(c->db,key,val);
    if (retval == REDIS_ERR) {
        if (!nx) {
