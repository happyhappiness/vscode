robj *dupStringObject(robj *o) {
    redisAssertWithInfo(NULL,o,o->encoding == REDIS_ENCODING_RAW);
    return createStringObject(o->ptr,sdslen(o->ptr));
}