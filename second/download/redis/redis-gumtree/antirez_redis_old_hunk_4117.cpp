        server.appendseldb = dictid;
    }

    /* "Fix" the argv vector if the command is EXPIRE. We want to translate
     * EXPIREs into EXPIREATs calls */
    if (cmd->proc == expireCommand) {
        long when;

        tmpargv[0] = createStringObject("EXPIREAT",8);
        tmpargv[1] = argv[1];
        incrRefCount(argv[1]);
        when = time(NULL)+strtol(argv[2]->ptr,NULL,10);
        tmpargv[2] = createObject(REDIS_STRING,
            sdscatprintf(sdsempty(),"%ld",when));
        argv = tmpargv;
    }

    /* Append the actual command */
    buf = sdscatprintf(buf,"*%d\r\n",argc);
    for (j = 0; j < argc; j++) {
        robj *o = argv[j];

        o = getDecodedObject(o);
        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
        buf = sdscatlen(buf,"\r\n",2);
        decrRefCount(o);
    }

    /* Free the objects from the modified argv for EXPIREAT */
    if (cmd->proc == expireCommand) {
        for (j = 0; j < 3; j++)
            decrRefCount(argv[j]);
    }

    /* Append to the AOF buffer. This will be flushed on disk just before
