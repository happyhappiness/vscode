    }

    value += incr;
    new = createStringObjectFromLongLong(value);
    hashTryObjectEncoding(o,&c->argv[2],NULL);
    hashSet(o,c->argv[2],new);
    decrRefCount(new);
    addReplyLongLong(c,value);
