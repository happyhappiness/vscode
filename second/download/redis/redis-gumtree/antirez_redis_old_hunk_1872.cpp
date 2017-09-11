        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
            return;
        if (milliseconds <= 0) {
            addReplyError(c,"invalid expire time in SETEX");
            return;
        }
        if (unit == UNIT_SECONDS) milliseconds *= 1000;
