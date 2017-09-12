
    value += incr;
    o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
    retval = dictAdd(c->dict,c->argv[1],o);
    if (retval == DICT_ERR) {
        dictReplace(c->dict,c->argv[1],o);
    } else {
        incrRefCount(c->argv[1]);
    }
