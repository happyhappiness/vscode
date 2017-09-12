    return createObject(REDIS_STRING,sdsnewlen(ptr,len));
}

static robj *dupStringObject(robj *o) {
    assert(o->encoding == REDIS_ENCODING_RAW);
    return createStringObject(o->ptr,sdslen(o->ptr));
