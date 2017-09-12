    for (j = 0; j < argc; j++) {
        robj *o = argv[j];

        if (o->encoding != REDIS_ENCODING_RAW)
            o = getDecodedObject(o);
        buf = sdscatprintf(buf,"$%d\r\n",sdslen(o->ptr));
        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
        buf = sdscatlen(buf,"\r\n",2);
        if (o != argv[j])
            decrRefCount(o);
    }

    /* Free the objects from the modified argv for EXPIREAT */
