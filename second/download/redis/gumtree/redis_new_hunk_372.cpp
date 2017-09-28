        redisAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',2));
        redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"SELECT",6));
        redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,dbid));
    }

    /* Create RESTORE payload and generate the protocol to call the command. */
    for (j = 0; j < num_keys; j++) {
        expireat = getExpire(c->db,kv[j]);
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
        redisAssertWithInfo(c,NULL,sdsEncodedObject(kv[j]));
        redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,kv[j]->ptr,
                sdslen(kv[j]->ptr)));
        redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,ttl));

        /* Emit the payload argument, that is the serialized object using
         * the DUMP format. */
        createDumpPayload(&payload,ov[j]);
        redisAssertWithInfo(c,NULL,
            rioWriteBulkString(&cmd,payload.io.buffer.ptr,
                               sdslen(payload.io.buffer.ptr)));
        sdsfree(payload.io.buffer.ptr);

        /* Add the REPLACE option to the RESTORE command if it was specified
         * as a MIGRATE option. */
        if (replace)
            redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"REPLACE",7));
    }

    /* Transfer the query to the other node in 64K chunks. */
    errno = 0;
    {
        sds buf = cmd.io.buffer.ptr;
        size_t pos = 0, towrite;
        int nwritten = 0;

        while ((towrite = sdslen(buf)-pos) > 0) {
            towrite = (towrite > (64*1024) ? (64*1024) : towrite);
            nwritten = syncWrite(cs->fd,buf+pos,towrite,timeout);
            if (nwritten != (signed)towrite) {
                write_error = 1;
                goto socket_err;
            }
            pos += nwritten;
        }
    }

    char buf1[1024]; /* Select reply. */
    char buf2[1024]; /* Restore reply. */

    /* Read the SELECT reply if needed. */
    if (select && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
        goto socket_err;

    /* Read the RESTORE replies. */
    int error_from_target = 0;
    int del_idx = 1; /* Index of the key argument for the replicated DEL op. */
    robj **newargv = NULL;

    if (!copy) newargv = zmalloc(sizeof(robj*)*(num_keys+1));

    for (j = 0; j < num_keys; j++) {
        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
            goto socket_err;
        if ((select && buf1[0] == '-') || buf2[0] == '-') {
            /* On error assume that last_dbid is no longer valid. */
            if (!error_from_target) {
                cs->last_dbid = -1;
                addReplyErrorFormat(c,"Target instance replied with error: %s",
                    (select && buf1[0] == '-') ? buf1+1 : buf2+1);
                error_from_target = 1;
            }
        } else {
            if (!copy) {
                /* No COPY option: remove the local key, signal the change. */
                dbDelete(c->db,kv[j]);
                signalModifiedKey(c->db,kv[j]);
                server.dirty++;

                /* Populate the argument vector to replace the old one. */
                newargv[del_idx++] = kv[j];
                incrRefCount(kv[j]);
            }
        }
    }

    if (!copy) {
        /* Translate MIGRATE as DEL for replication/AOF. */
        if (del_idx > 1) {
            newargv[0] = createStringObject("DEL",3);
            replaceClientCommandVector(c,del_idx,newargv);
        } else {
            /* No key transfer acknowledged, no need to rewrite as DEL. */
            zfree(newargv);
        }
    }

    if (!error_from_target) {
        /* Update the last_dbid in migrateCachedSocket and reply +OK. */
        cs->last_dbid = dbid;
        addReply(c,shared.ok);
    } else {
        /* On error we already sent it in the for loop above. */
    }

    sdsfree(cmd.io.buffer.ptr);
    zfree(ov); zfree(kv);
    return;

/* On socket errors we try to close the cached socket and try again.
 * It is very common for the cached socket to get closed, if just reopening
 * it works it's a shame to notify the error to the caller. */
socket_err:
    sdsfree(cmd.io.buffer.ptr);
    migrateCloseSocket(c->argv[1],c->argv[2]);
    if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
    zfree(ov); zfree(kv);
    addReplySds(c,
        sdscatprintf(sdsempty(),
            "-IOERR error or timeout %s to target instance\r\n",
            write_error ? "writing" : "reading"));
    return;
}

/* -----------------------------------------------------------------------------
 * Cluster functions related to serving / redirecting clients
 * -------------------------------------------------------------------------- */
