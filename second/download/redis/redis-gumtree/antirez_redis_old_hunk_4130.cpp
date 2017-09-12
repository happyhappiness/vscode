    return bothsds ? sdscmp(astr,bstr) : strcmp(astr,bstr);
}

static size_t stringObjectLen(robj *o) {
    redisAssert(o->type == REDIS_STRING);
    if (o->encoding == REDIS_ENCODING_RAW) {
        return sdslen(o->ptr);
    } else {
        char buf[32];

        return snprintf(buf,32,"%ld",(long)o->ptr);
    }
}

