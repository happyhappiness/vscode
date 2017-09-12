    }
}

static robj *lookupKey(redisDb *db, robj *key) {
    dictEntry *de = dictFind(db->dict,key);
    return de ? dictGetEntryVal(de) : NULL;
}

static robj *lookupKeyRead(redisDb *db, robj *key) {
    expireIfNeeded(db,key);
    return lookupKey(db,key);
}

static robj *lookupKeyWrite(redisDb *db, robj *key) {
    deleteIfVolatile(db,key);
    return lookupKey(db,key);
}

static int deleteKey(redisDb *db, robj *key) {
    int retval;

    /* We need to protect key from destruction: after the first dictDelete()
     * it may happen that 'key' is no longer valid if we don't increment
     * it's count. This may happen when we get the object reference directly
     * from the hash table with dictRandomKey() or dict iterators */
    incrRefCount(key);
    if (dictSize(db->expires)) dictDelete(db->expires,key);
    retval = dictDelete(db->dict,key);
    decrRefCount(key);

    return retval == DICT_OK;
}

/*============================ DB saving/loading ============================ */
