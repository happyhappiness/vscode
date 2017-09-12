
    value += incr;
    new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
    hashReplace(o,c->argv[2],new);
    decrRefCount(new);
    addReplyLongLong(c,value);
    server.dirty++;
