    return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
}

static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
    int isencoded;
    uint32_t len;
