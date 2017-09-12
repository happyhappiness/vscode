        robj *o = argv[j];

        o = getDecodedObject(o);
        buf = sdscatprintf(buf,"$%d\r\n",sdslen(o->ptr));
        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
        buf = sdscatlen(buf,"\r\n",2);
        decrRefCount(o);
