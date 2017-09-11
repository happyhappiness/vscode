        goto error;
    }

    /* Delete the readable event, we no longer need it now that there is
     * the last reply to read. */
    aeDeleteFileEvent(server.el,fd,AE_READABLE);
    psync_result = slaveTryPartialResynchronization(fd,1);
    if (psync_result == PSYNC_WAIT_REPLY) {
        if (aeCreateFileEvent(server.el,fd,AE_READABLE,
            syncWithMaster,NULL) == AE_ERR)
        {
            serverLog(LL_WARNING,"Failed to reinstall the read event in "
                                 "PSYNC_WAIT_REPLY state.");
            goto error;
        }
        return; /* Try again later... */
    }

    if (psync_result == PSYNC_CONTINUE) {
        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
