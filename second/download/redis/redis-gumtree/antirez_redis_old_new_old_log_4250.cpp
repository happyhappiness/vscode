addReplySds(c,sdscatprintf(sdsempty(),
            "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d serializedlength:%lld\r\n",
                (void*)key, key->refcount, (void*)val, val->refcount,
                val->encoding, rdbSavedObjectLen(val)));