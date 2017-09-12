
    o = lookupKeyWrite(c->db,c->argv[1]);

    if (getLongLongFromObjectOrReply(c, o, &value, NULL) != REDIS_OK) return;

    value += incr;
    o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
