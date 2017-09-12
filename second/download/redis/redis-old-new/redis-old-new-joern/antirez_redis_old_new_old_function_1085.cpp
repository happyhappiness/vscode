void hashTypeConvertZiplist(robj *o, int enc) {
    serverAssert(o->encoding == OBJ_ENCODING_ZIPLIST);

    if (enc == OBJ_ENCODING_ZIPLIST) {
        /* Nothing to do... */

    } else if (enc == OBJ_ENCODING_HT) {
        hashTypeIterator *hi;
        dict *dict;
        int ret;

        hi = hashTypeInitIterator(o);
        dict = dictCreate(&hashDictType, NULL);

        while (hashTypeNext(hi) != C_ERR) {
            robj *field, *value;

            field = hashTypeCurrentObject(hi, OBJ_HASH_KEY);
            field = tryObjectEncoding(field);
            value = hashTypeCurrentObject(hi, OBJ_HASH_VALUE);
            value = tryObjectEncoding(value);
            ret = dictAdd(dict, field, value);
            if (ret != DICT_OK) {
                serverLogHexDump(REDIS_WARNING,"ziplist with dup elements dump",
                    o->ptr,ziplistBlobLen(o->ptr));
                serverAssert(ret == DICT_OK);
            }
        }

        hashTypeReleaseIterator(hi);
        zfree(o->ptr);

        o->encoding = OBJ_ENCODING_HT;
        o->ptr = dict;

    } else {
        redisPanic("Unknown hash encoding");
    }
}