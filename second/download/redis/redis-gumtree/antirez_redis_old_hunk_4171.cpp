
    o = lookupKeyWrite(c->db,c->argv[1]);

    if (getLongLongFromObject(c, o, &value) != REDIS_OK) return;

    value += incr;
    o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
