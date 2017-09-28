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
