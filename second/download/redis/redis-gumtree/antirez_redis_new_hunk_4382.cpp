    for (j = 0; j < argc; j++) {
        robj *o = argv[j];

        o = getDecodedObject(o);
        buf = sdscatprintf(buf,"$%d\r\n",sdslen(o->ptr));
        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
        buf = sdscatlen(buf,"\r\n",2);
        decrRefCount(o);
    }

    /* Free the objects from the modified argv for EXPIREAT */
