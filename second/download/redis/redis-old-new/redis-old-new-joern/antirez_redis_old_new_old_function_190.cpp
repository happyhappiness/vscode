int slaveTryPartialResynchronization(int fd, int read_reply) {
    char *psync_runid;
    char psync_offset[32];
    sds reply;

    /* Writing half */
    if (!read_reply) {
        /* Initially set repl_master_initial_offset to -1 to mark the current
         * master run_id and offset as not valid. Later if we'll be able to do
         * a FULL resync using the PSYNC command we'll set the offset at the
         * right value, so that this information will be propagated to the
         * client structure representing the master into server.master. */
        server.repl_master_initial_offset = -1;

        if (server.cached_master) {
            psync_runid = server.cached_master->replrunid;
            snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
            serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
        } else {
            serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
            psync_runid = "?";
            memcpy(psync_offset,"-1",3);
        }

        /* Issue the PSYNC command */
        reply = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"PSYNC",psync_runid,psync_offset,NULL);
        if (reply != NULL) {
            serverLog(LL_WARNING,"Unable to send PSYNC to master: %s",reply);
            sdsfree(reply);
            aeDeleteFileEvent(server.el,fd,AE_READABLE);
            return PSYNC_WRITE_ERROR;
        }
        return PSYNC_WAIT_REPLY;
    }

    /* Reading half */
    reply = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
    if (sdslen(reply) == 0) {
        /* The master may send empty newlines after it receives PSYNC
         * and before to reply, just to keep the connection alive. */
        sdsfree(reply);
        return PSYNC_WAIT_REPLY;
    }

    aeDeleteFileEvent(server.el,fd,AE_READABLE);

    if (!strncmp(reply,"+FULLRESYNC",11)) {
        char *runid = NULL, *offset = NULL;

        /* FULL RESYNC, parse the reply in order to extract the run id
         * and the replication offset. */
        runid = strchr(reply,' ');
        if (runid) {
            runid++;
            offset = strchr(runid,' ');
            if (offset) offset++;
        }
        if (!runid || !offset || (offset-runid-1) != CONFIG_RUN_ID_SIZE) {
            serverLog(LL_WARNING,
                "Master replied with wrong +FULLRESYNC syntax.");
            /* This is an unexpected condition, actually the +FULLRESYNC
             * reply means that the master supports PSYNC, but the reply
             * format seems wrong. To stay safe we blank the master
             * runid to make sure next PSYNCs will fail. */
            memset(server.repl_master_runid,0,CONFIG_RUN_ID_SIZE+1);
        } else {
            memcpy(server.repl_master_runid, runid, offset-runid-1);
            server.repl_master_runid[CONFIG_RUN_ID_SIZE] = '\0';
            server.repl_master_initial_offset = strtoll(offset,NULL,10);
            serverLog(LL_NOTICE,"Full resync from master: %s:%lld",
                server.repl_master_runid,
                server.repl_master_initial_offset);
        }
        /* We are going to full resync, discard the cached master structure. */
        replicationDiscardCachedMaster();
        sdsfree(reply);
        return PSYNC_FULLRESYNC;
    }

    if (!strncmp(reply,"+CONTINUE",9)) {
        /* Partial resync was accepted, set the replication state accordingly */
        serverLog(LL_NOTICE,
            "Successful partial resynchronization with master.");
        sdsfree(reply);
        replicationResurrectCachedMaster(fd);
        return PSYNC_CONTINUE;
    }

    /* If we reach this point we received either an error since the master does
     * not understand PSYNC, or an unexpected reply from the master.
     * Return PSYNC_NOT_SUPPORTED to the caller in both cases. */

    if (strncmp(reply,"-ERR",4)) {
        /* If it's not an error, log the unexpected event. */
        serverLog(LL_WARNING,
            "Unexpected reply to PSYNC from master: %s", reply);
    } else {
        serverLog(LL_NOTICE,
            "Master does not support PSYNC or is in "
            "error state (reply: %s)", reply);
    }
    sdsfree(reply);
    replicationDiscardCachedMaster();
    return PSYNC_NOT_SUPPORTED;
}