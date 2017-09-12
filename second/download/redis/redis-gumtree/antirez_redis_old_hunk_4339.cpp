        key = dictGetEntryKey(de);
        val = dictGetEntryVal(de);
        addReplySds(c,sdscatprintf(sdsempty(),
            "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d\r\n",
                (void*)key, key->refcount, (void*)val, val->refcount,
                val->encoding));
    } else {
        addReplySds(c,sdsnew(
            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|RELOAD]\r\n"));
