        if (getLongFromObjectOrReply(c, expire, &seconds, NULL) != REDIS_OK)
            return;
        if (seconds <= 0) {
            addReplyError(c,"invalid expire time in SETEX");
            return;
        }
    }

    retval = dbAdd(c->db,key,val);
    if (retval == REDIS_ERR) {
        if (!nx) {
