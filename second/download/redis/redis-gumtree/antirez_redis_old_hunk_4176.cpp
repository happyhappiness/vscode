    }

    value += incr;
    new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
    hashSet(o,c->argv[2],new);
    decrRefCount(new);
    addReplyLongLong(c,value);
