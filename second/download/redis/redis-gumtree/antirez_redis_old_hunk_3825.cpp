        if (getLongFromObjectOrReply(c, expire, &seconds, NULL) != REDIS_OK)
            return;
        if (seconds <= 0) {
            addReplySds(c,sdsnew("-ERR invalid expire time in SETEX\r\n"));
            return;
        }
    }
