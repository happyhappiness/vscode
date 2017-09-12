    addReply(c,lenobj);
    decrRefCount(lenobj);

    hi = hashInitIterator(o);
    while (hashNext(hi) != REDIS_ERR) {
        if (flags & REDIS_HASH_KEY) {
            obj = hashCurrent(hi,REDIS_HASH_KEY);
            addReplyBulk(c,obj);
            decrRefCount(obj);
            count++;
        }
        if (flags & REDIS_HASH_VALUE) {
            obj = hashCurrent(hi,REDIS_HASH_VALUE);
            addReplyBulk(c,obj);
            decrRefCount(obj);
            count++;
        }
    }
    hashReleaseIterator(hi);

    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
}
