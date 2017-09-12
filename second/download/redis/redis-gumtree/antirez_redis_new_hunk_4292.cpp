                "+Key at:%p refcount:%d, value at:%p refcount:%d "
                "encoding:%d serializedlength:%lld\r\n",
                (void*)key, key->refcount, (void*)val, val->refcount,
                val->encoding, (long long) rdbSavedObjectLen(val,NULL)));
        } else {
            addReplySds(c,sdscatprintf(sdsempty(),
                "+Key at:%p refcount:%d, value swapped at: page %llu "
