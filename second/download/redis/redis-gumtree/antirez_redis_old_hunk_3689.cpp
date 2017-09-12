        if (o->encoding == REDIS_ENCODING_RAW) {
            value = strtoll(o->ptr, &eptr, 10);
            if (eptr[0] != '\0') return REDIS_ERR;
        } else if (o->encoding == REDIS_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            redisPanic("Unknown string encoding");
        }
    }

    *target = value;
    return REDIS_OK;
}

int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, const char *msg) {
    long long value;
    if (getLongLongFromObject(o, &value) != REDIS_OK) {
        if (msg != NULL) {
            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
        } else {
            addReplySds(c, sdsnew("-ERR value is not an integer\r\n"));
        }
        return REDIS_ERR;
    }
