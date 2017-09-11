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
    for (j = 0; j < num_keys; j++) {
        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
            goto socket_err;
        if (error_from_target) continue; /* Just consume the replies. */
        if ((select && buf1[0] == '-') || buf2[0] == '-') {
            /* On error assume that last_dbid is no longer valid. */
            cs->last_dbid = -1;
            addReplyErrorFormat(c,"Target instance replied with error: %s",
                (select && buf1[0] == '-') ? buf1+1 : buf2+1);
            error_from_target = 1;
        } else {
            if (!copy) {
                robj *aux;

                /* No COPY option: remove the local key, signal the change. */
                dbDelete(c->db,kv[j]);
                signalModifiedKey(c->db,kv[j]);
                server.dirty++;

                /* Translate MIGRATE as DEL for replication/AOF. */
                if (j == 0) {
                    aux = createStringObject("DEL",3);
                    rewriteClientCommandArgument(c,0,aux);
                    decrRefCount(aux);
                }
                rewriteClientCommandArgument(c,j+1,kv[j]);
            }
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

