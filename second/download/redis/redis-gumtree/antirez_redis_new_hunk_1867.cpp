{
    sentinelRedisInstance *ri;

    ri = dictFetchValue(sentinel.masters,name->ptr);
    if (!ri) {
        addReplyError(c,"No such master with that name");
        return NULL;
