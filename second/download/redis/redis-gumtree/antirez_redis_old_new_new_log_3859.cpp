s(c,sdscatprintf(sdsempty(),
                "+Value at:%p refcount:%d "
                "encoding:%s serializedlength:%lld\r\n",
                (void*)val, val->refcount,
                strenc, (long long) rdbSavedObjectLen(val,NULL)));