addReplySds(c,sdscatprintf(sdsempty(),
                "+Key at:%p refcount:%d, value at:%p refcount:%d "
                "encoding:%s serializedlength:%lld\r\n",
                (void*)key, key->refcount, (void*)val, val->refcount,
                strenc, (long long) rdbSavedObjectLen(val,NULL)));