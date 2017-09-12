    } else if (!strcasecmp(c->argv[1]->ptr,"object") && c->argc == 3) {
        dictEntry *de = dictFind(c->db->dict,c->argv[2]->ptr);
        robj *val;
        char *strenc;
        char *storage;

        if (!de) {
            addReply(c,shared.nokeyerr);
            return;
        }
        val = dictGetEntryVal(de);
        strenc = strEncoding(val->encoding);
        switch(val->storage) {
        case REDIS_DS_MEMORY: storage = "memory"; break;
        case REDIS_DS_DIRTY: storage = "dirty"; break;
        case REDIS_DS_SAVING: storage = "saving"; break;
        default: storage = "unknown"; break;
        }
        addReplyStatusFormat(c,
            "Value at:%p refcount:%d "
            "encoding:%s serializedlength:%lld "
            "lru:%d lru_seconds_idle:%lu storage:%s",
            (void*)val, val->refcount,
            strenc, (long long) rdbSavedObjectLen(val),
            val->lru, estimateObjectIdleTime(val), storage);
    } else if (!strcasecmp(c->argv[1]->ptr,"populate") && c->argc == 3) {
        long keys, j;
        robj *key, *val;
