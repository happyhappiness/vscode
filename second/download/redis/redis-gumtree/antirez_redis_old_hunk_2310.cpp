            (void*)val, val->refcount,
            strenc, (long long) rdbSavedObjectLen(val),
            val->lru, estimateObjectIdleTime(val));
    } else if (!strcasecmp(c->argv[1]->ptr,"populate") && c->argc == 3) {
        long keys, j;
        robj *key, *val;
