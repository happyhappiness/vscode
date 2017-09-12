void migrateCommand(redisClient *c) {
    int fd;
    long timeout;
    long dbid;
    time_t ttl;
    robj *o;
    rio cmd, payload;

    /* Sanity check */
    if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != REDIS_OK)
        return;
    if (getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != REDIS_OK)
        return;
    if (timeout <= 0) timeout = 1;

    /* Check if the key is here. If not we reply with success as there is
     * nothing to migrate (for instance the key expired in the meantime), but
     * we include such information in the reply string. */
    if ((o = lookupKeyRead(c->db,c->argv[3])) == NULL) {
        addReplySds(c,sdsnew("+NOKEY"));
        return;
    }
    
    /* Connect */
    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
                atoi(c->argv[2]->ptr));
    if (fd == -1) {
        addReplyErrorFormat(c,"Can't connect to target node: %s",
            server.neterr);
        return;
    }
    if ((aeWait(fd,AE_WRITABLE,timeout*1000) & AE_WRITABLE) == 0) {
        addReplyError(c,"Timeout connecting to the client");
        return;
    }

    cmd = rioInitWithBuffer(sdsempty());
    redisAssert(rioWriteBulkCount(&cmd,'*',2));
    redisAssert(rioWriteBulkString(&cmd,"SELECT",6));
    redisAssert(rioWriteBulkLongLong(&cmd,dbid));

    ttl = getExpire(c->db,c->argv[3]);
    redisAssert(rioWriteBulkCount(&cmd,'*',4));
    redisAssert(rioWriteBulkString(&cmd,"RESTORE",7));
    redisAssert(c->argv[3]->encoding == REDIS_ENCODING_RAW);
    redisAssert(rioWriteBulkString(&cmd,c->argv[3]->ptr,sdslen(c->argv[3]->ptr)));
    redisAssert(rioWriteBulkLongLong(&cmd,(ttl == -1) ? 0 : ttl));

    /* Finally the last argument that is the serailized object payload
     * in the form: <type><rdb-serialized-object>. */
    payload = rioInitWithBuffer(sdsempty());
    redisAssert(rdbSaveObjectType(&payload,o));
    redisAssert(rdbSaveObject(&payload,o) != -1);
    redisAssert(rioWriteBulkString(&cmd,payload.io.buffer.ptr,sdslen(payload.io.buffer.ptr)));
    sdsfree(payload.io.buffer.ptr);

    /* Tranfer the query to the other node in 64K chunks. */
    {
        sds buf = cmd.io.buffer.ptr;
        size_t pos = 0, towrite;
        int nwritten = 0;

        while ((towrite = sdslen(buf)-pos) > 0) {
            towrite = (towrite > (64*1024) ? (64*1024) : towrite);
            nwritten = syncWrite(fd,buf+nwritten,towrite,timeout);
            if (nwritten != (signed)towrite) goto socket_wr_err;
            pos += nwritten;
        }
    }

    /* Read back the reply. */
    {
        char buf1[1024];
        char buf2[1024];

        /* Read the two replies */
        if (syncReadLine(fd, buf1, sizeof(buf1), timeout) <= 0)
            goto socket_rd_err;
        if (syncReadLine(fd, buf2, sizeof(buf2), timeout) <= 0)
            goto socket_rd_err;
        if (buf1[0] == '-' || buf2[0] == '-') {
            addReplyErrorFormat(c,"Target instance replied with error: %s",
                (buf1[0] == '-') ? buf1+1 : buf2+1);
        } else {
            dbDelete(c->db,c->argv[3]);
            addReply(c,shared.ok);
        }
    }

    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;

socket_wr_err:
    redisLog(REDIS_NOTICE,"Can't write to target node for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
        strerror(errno));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;

socket_rd_err:
    redisLog(REDIS_NOTICE,"Can't read from target node for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, reading from target node: %s.",
        strerror(errno));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;
}