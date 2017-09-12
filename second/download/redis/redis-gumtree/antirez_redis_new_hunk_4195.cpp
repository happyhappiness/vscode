
        value += incr;
        hval = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
        hval = tryObjectEncoding(hval);
        if (dictReplace(o->ptr,c->argv[2],hval)) {
            incrRefCount(c->argv[2]);
        }
