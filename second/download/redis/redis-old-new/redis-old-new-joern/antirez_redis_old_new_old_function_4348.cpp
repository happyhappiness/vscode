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
            redisLog(REDIS_WARNING,"Aborting on error writing to the append-only file: %s",strerror(errno));
         } else {
            redisLog(REDIS_WARNING,"Aborting on short write while writing to the append-only file: %s",strerror(errno));
         }
         abort();
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