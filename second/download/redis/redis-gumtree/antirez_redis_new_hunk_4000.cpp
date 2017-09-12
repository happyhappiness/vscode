    addReply(c,lenobj);
    decrRefCount(lenobj);

    hi = hashTypeInitIterator(o);
    while (hashTypeNext(hi) != REDIS_ERR) {
        if (flags & REDIS_HASH_KEY) {
            obj = hashTypeCurrent(hi,REDIS_HASH_KEY);
            addReplyBulk(c,obj);
            decrRefCount(obj);
            count++;
        }
        if (flags & REDIS_HASH_VALUE) {
            obj = hashTypeCurrent(hi,REDIS_HASH_VALUE);
            addReplyBulk(c,obj);
            decrRefCount(obj);
            count++;
        }
    }
    hashTypeReleaseIterator(hi);

    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
}
