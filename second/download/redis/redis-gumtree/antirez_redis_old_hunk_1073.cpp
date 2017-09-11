    long long tval;

    if (getLongLongFromObjectOrReply(c,object,&tval,
        "timeout is not an integer or out of range") != REDIS_OK)
        return REDIS_ERR;

    if (tval < 0) {
        addReplyError(c,"timeout is negative");
        return REDIS_ERR;
    }

    if (tval > 0) {
