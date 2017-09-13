(cmd->proc == expireCommand) {
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