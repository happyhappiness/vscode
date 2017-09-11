            value = tryObjectEncoding(value);
            ret = dictAdd(dict, field, value);
            if (ret != DICT_OK) {
                serverLogHexDump(LL_WARNING,"ziplist with dup elements dump",
                    o->ptr,ziplistBlobLen(o->ptr));
                serverAssert(ret == DICT_OK);
            }
