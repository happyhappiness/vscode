        redisAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',2));
        redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"SELECT",6));
        redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,dbid));
    }

    /* Create RESTORE payload and generate the protocol to call the command. */
    expireat = getExpire(c->db,c->argv[3]);
    if (expireat != -1) {
        ttl = expireat-mstime();
        if (ttl < 1) ttl = 1;
    }
    redisAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',replace ? 5 : 4));
    if (server.cluster_enabled)
        redisAssertWithInfo(c,NULL,
            rioWriteBulkString(&cmd,"RESTORE-ASKING",14));
    else
        redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"RESTORE",7));
    redisAssertWithInfo(c,NULL,sdsEncodedObject(c->argv[3]));
    redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,c->argv[3]->ptr,
            sdslen(c->argv[3]->ptr)));
    redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,ttl));

    /* Emit the payload argument, that is the serialized object using
     * the DUMP format. */
    createDumpPayload(&payload,o);
    redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,payload.io.buffer.ptr,
                                sdslen(payload.io.buffer.ptr)));
    sdsfree(payload.io.buffer.ptr);

    /* Add the REPLACE option to the RESTORE command if it was specified
     * as a MIGRATE option. */
    if (replace)
        redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"REPLACE",7));

    /* Transfer the query to the other node in 64K chunks. */
    errno = 0;
    {
        sds buf = cmd.io.buffer.ptr;
        size_t pos = 0, towrite;
        int nwritten = 0;

        while ((towrite = sdslen(buf)-pos) > 0) {
            towrite = (towrite > (64*1024) ? (64*1024) : towrite);
            nwritten = syncWrite(cs->fd,buf+pos,towrite,timeout);
            if (nwritten != (signed)towrite) goto socket_wr_err;
            pos += nwritten;
        }
    }

    /* Read back the reply. */
    {
        char buf1[1024];
        char buf2[1024];

        /* Read the two replies */
        if (select && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
            goto socket_rd_err;
        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
            goto socket_rd_err;
        if ((select && buf1[0] == '-') || buf2[0] == '-') {
            /* On error assume that last_dbid is no longer valid. */
            cs->last_dbid = -1;
            addReplyErrorFormat(c,"Target instance replied with error: %s",
                (select && buf1[0] == '-') ? buf1+1 : buf2+1);
        } else {
            /* Update the last_dbid in migrateCachedSocket */
            cs->last_dbid = dbid;
            robj *aux;

            addReply(c,shared.ok);

            if (!copy) {
                /* No COPY option: remove the local key, signal the change. */
                dbDelete(c->db,c->argv[3]);
                signalModifiedKey(c->db,c->argv[3]);
                server.dirty++;

                /* Translate MIGRATE as DEL for replication/AOF. */
                aux = createStringObject("DEL",3);
                rewriteClientCommandVector(c,2,aux,c->argv[3]);
                decrRefCount(aux);
            }
        }
    }

    sdsfree(cmd.io.buffer.ptr);
    return;

socket_wr_err:
    sdsfree(cmd.io.buffer.ptr);
    migrateCloseSocket(c->argv[1],c->argv[2]);
    if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
    addReplySds(c,
        sdsnew("-IOERR error or timeout writing to target instance\r\n"));
    return;

socket_rd_err:
    sdsfree(cmd.io.buffer.ptr);
    migrateCloseSocket(c->argv[1],c->argv[2]);
    if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
    addReplySds(c,
        sdsnew("-IOERR error or timeout reading from target node\r\n"));
    return;
}

/* -----------------------------------------------------------------------------
 * Cluster functions related to serving / redirecting clients
 * -------------------------------------------------------------------------- */
