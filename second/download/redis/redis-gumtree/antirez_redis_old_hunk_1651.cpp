        val = dictGetVal(de);
        strenc = strEncoding(val->encoding);

        addReplyStatusFormat(c,
            "Value at:%p refcount:%d "
            "encoding:%s serializedlength:%lld "
            "lru:%d lru_seconds_idle:%llu",
            (void*)val, val->refcount,
            strenc, (long long) rdbSavedObjectLen(val),
            val->lru, estimateObjectIdleTime(val)/1000);
    } else if (!strcasecmp(c->argv[1]->ptr,"sdslen") && c->argc == 3) {
        dictEntry *de;
        robj *val;
