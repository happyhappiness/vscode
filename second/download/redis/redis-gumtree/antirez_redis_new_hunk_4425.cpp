    }
}

/* ============================== Append Only file ========================== */

static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
    sds buf = sdsempty();
    int j;
    ssize_t nwritten;
    time_t now;
    robj *tmpargv[3];

    /* The DB this command was targetting is not the same as the last command
     * we appendend. To issue a SELECT command is needed. */
    if (dictid != server.appendseldb) {
        char seldb[64];

        snprintf(seldb,sizeof(seldb),"%d",dictid);
        buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
            strlen(seldb),seldb);
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

        if (o->encoding != REDIS_ENCODING_RAW)
            o = getDecodedObject(o);
        buf = sdscatprintf(buf,"$%d\r\n",sdslen(o->ptr));
        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
        buf = sdscatlen(buf,"\r\n",2);
        if (o != argv[j])
            decrRefCount(o);
    }

    /* Free the objects from the modified argv for EXPIREAT */
    if (cmd->proc == expireCommand) {
        for (j = 0; j < 3; j++)
            decrRefCount(argv[j]);
    }

    /* We want to perform a single write. This should be guaranteed atomic
     * at least if the filesystem we are writing is a real physical one.
     * While this will save us against the server being killed I don't think
     * there is much to do about the whole server stopping for power problems
     * or alike */
     nwritten = write(server.appendfd,buf,sdslen(buf));
     if (nwritten != (signed)sdslen(buf)) {
        /* Ooops, we are in troubles. The best thing to do for now is
         * to simply exit instead to give the illusion that everything is
         * working as expected. */
         if (nwritten == -1) {
            redisLog(REDIS_WARNING,"Exiting on error writing to the append-only file: %s",strerror(errno));
         } else {
            redisLog(REDIS_WARNING,"Exiting on short write while writing to the append-only file: %s",strerror(errno));
         }
         exit(1);
    }
    now = time(NULL);
    if (server.appendfsync == APPENDFSYNC_ALWAYS ||
        (server.appendfsync == APPENDFSYNC_EVERYSEC &&
         now-server.lastfsync > 1))
    {
        fsync(server.appendfd); /* Let's try to get this data on the disk */
        server.lastfsync = now;
    }
}

/* In Redis commands are always executed in the context of a client, so in
 * order to load the append only file we need to create a fake client. */
static struct redisClient *createFakeClient(void) {
    struct redisClient *c = zmalloc(sizeof(*c));

    selectDb(c,0);
    c->fd = -1;
    c->querybuf = sdsempty();
    c->argc = 0;
    c->argv = NULL;
    c->flags = 0;
    c->reply = listCreate();
    listSetFreeMethod(c->reply,decrRefCount);
    listSetDupMethod(c->reply,dupClientReplyValue);
    return c;
}

static void freeFakeClient(struct redisClient *c) {
    sdsfree(c->querybuf);
    listRelease(c->reply);
    zfree(c);
}

/* Replay the append log file. On error REDIS_OK is returned. On non fatal
 * error (the append only file is zero-length) REDIS_ERR is returned. On
 * fatal error an error message is logged and the program exists. */
int loadAppendOnlyFile(char *filename) {
    struct redisClient *fakeClient;
    FILE *fp = fopen(filename,"r");
    struct redis_stat sb;

    if (redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0)
        return REDIS_ERR;

    if (fp == NULL) {
        redisLog(REDIS_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
        exit(1);
    }

    fakeClient = createFakeClient();
    while(1) {
        int argc, j;
        unsigned long len;
        robj **argv;
        char buf[128];
        sds argsds;
        struct redisCommand *cmd;

        if (fgets(buf,sizeof(buf),fp) == NULL) {
            if (feof(fp))
                break;
            else
                goto readerr;
        }
        if (buf[0] != '*') goto fmterr;
        argc = atoi(buf+1);
        argv = zmalloc(sizeof(robj*)*argc);
        for (j = 0; j < argc; j++) {
            if (fgets(buf,sizeof(buf),fp) == NULL) goto readerr;
            if (buf[0] != '$') goto fmterr;
            len = strtol(buf+1,NULL,10);
            argsds = sdsnewlen(NULL,len);
            if (fread(argsds,len,1,fp) == 0) goto fmterr;
            argv[j] = createObject(REDIS_STRING,argsds);
            if (fread(buf,2,1,fp) == 0) goto fmterr; /* discard CRLF */
        }

        /* Command lookup */
        cmd = lookupCommand(argv[0]->ptr);
        if (!cmd) {
            redisLog(REDIS_WARNING,"Unknown command '%s' reading the append only file", argv[0]->ptr);
            exit(1);
        }
        /* Try object sharing and encoding */
        if (server.shareobjects) {
            int j;
            for(j = 1; j < argc; j++)
                argv[j] = tryObjectSharing(argv[j]);
        }
        if (cmd->flags & REDIS_CMD_BULK)
            tryObjectEncoding(argv[argc-1]);
        /* Run the command in the context of a fake client */
        fakeClient->argc = argc;
        fakeClient->argv = argv;
        cmd->proc(fakeClient);
        /* Discard the reply objects list from the fake client */
        while(listLength(fakeClient->reply))
            listDelNode(fakeClient->reply,listFirst(fakeClient->reply));
        /* Clean up, ready for the next command */
        for (j = 0; j < argc; j++) decrRefCount(argv[j]);
        zfree(argv);
    }
    fclose(fp);
    freeFakeClient(fakeClient);
    return REDIS_OK;

readerr:
    if (feof(fp)) {
        redisLog(REDIS_WARNING,"Unexpected end of file reading the append only file");
    } else {
        redisLog(REDIS_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
    }
    exit(1);
fmterr:
    redisLog(REDIS_WARNING,"Bad file format reading the append only file");
    exit(1);
}

/* ================================= Debugging ============================== */

static void debugCommand(redisClient *c) {
