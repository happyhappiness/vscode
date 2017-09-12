    long long lltimeout;

    if (getLongLongFromObject(object, &lltimeout) != REDIS_OK) {
        addReplyError(c, "timeout is not an integer");
        return REDIS_ERR;
    }

    if (lltimeout < 0) {
        addReplyError(c, "timeout is negative");
        return REDIS_ERR;
    }

    *timeout = lltimeout;
