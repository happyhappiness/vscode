        val = dictGetEntryVal(de);
        if (!server.vm_enabled || (key->storage == REDIS_VM_MEMORY ||
                                   key->storage == REDIS_VM_SWAPPING)) {
            char *strenc;
            char buf[128];

            if (val->encoding < (sizeof(strencoding)/sizeof(char*))) {
                strenc = strencoding[val->encoding];
            } else {
                snprintf(buf,64,"unknown encoding %d\n", val->encoding);
                strenc = buf;
            }
            addReplySds(c,sdscatprintf(sdsempty(),
                "+Key at:%p refcount:%d, value at:%p refcount:%d "
                "encoding:%s serializedlength:%lld\r\n",
                (void*)key, key->refcount, (void*)val, val->refcount,
                strenc, (long long) rdbSavedObjectLen(val,NULL)));
        } else {
            addReplySds(c,sdscatprintf(sdsempty(),
                "+Key at:%p refcount:%d, value swapped at: page %llu "
