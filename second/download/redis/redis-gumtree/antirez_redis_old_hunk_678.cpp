        dict = dictCreate(&hashDictType, NULL);

        while (hashTypeNext(hi) != C_ERR) {
            robj *field, *value;

            field = hashTypeCurrentObject(hi, OBJ_HASH_KEY);
            field = tryObjectEncoding(field);
            value = hashTypeCurrentObject(hi, OBJ_HASH_VALUE);
            value = tryObjectEncoding(value);
            ret = dictAdd(dict, field, value);
            if (ret != DICT_OK) {
                serverLogHexDump(LL_WARNING,"ziplist with dup elements dump",
                    o->ptr,ziplistBlobLen(o->ptr));
                serverAssert(ret == DICT_OK);
            }
        }

        hashTypeReleaseIterator(hi);
        zfree(o->ptr);

        o->encoding = OBJ_ENCODING_HT;
        o->ptr = dict;

    } else {
        serverPanic("Unknown hash encoding");
    }
