    double value;
    if (getDoubleFromObject(o, &value) != REDIS_OK) {
        if (msg != NULL) {
            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
        } else {
            addReplySds(c, sdsnew("-ERR value is not a double\r\n"));
        }
        return REDIS_ERR;
    }
