    return createObject(REDIS_STRING,sdsnewlen(ptr,len));
}

static robj *createStringObjectFromLongLong(long long value) {
    robj *o;
    if (value >= 0 && value < REDIS_SHARED_INTEGERS) {
        incrRefCount(shared.integers[value]);
        o = shared.integers[value];
    } else {
        o = createObject(REDIS_STRING, NULL);
        if (value >= LONG_MIN && value <= LONG_MAX) {
            o->encoding = REDIS_ENCODING_INT;
            o->ptr = (void*)((long)value);
        } else {
            o->ptr = sdscatprintf(sdsempty(),"%lld",value);
        }
    }
    return o;
}

static robj *dupStringObject(robj *o) {
    assert(o->encoding == REDIS_ENCODING_RAW);
    return createStringObject(o->ptr,sdslen(o->ptr));
