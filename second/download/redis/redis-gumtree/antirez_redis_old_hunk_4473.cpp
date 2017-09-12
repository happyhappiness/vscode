        key = dictGetEntryKey(de);
        val = dictGetEntryVal(de);
        addReplySds(c,sdscatprintf(sdsempty(),
            "+Key at:%p refcount:%d, value at:%p refcount:%d\r\n",
                key, key->refcount, val, val->refcount));
    } else {
        addReplySds(c,sdsnew(
            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
