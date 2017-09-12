int slaveTryPartialResynchronization(int fd) {
    char *psync_runid;
    char psync_offset[32];
    sds reply;

    /* Initially set repl_master_initial_offset to -1 to mark the current
     * master run_id and offset as not valid. Later if we'll be able to do
     * a FULL resync using the PSYNC command we'll set the offset at the
     * right value, so that this information will be propagated to the
     * client structure representing the master into server.master. */
    server.repl_master_initial_offset = -1;

    if (server.cached_master) {
        psync_runid = server.cached_master->replrunid;
        snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
        redisLog(REDIS_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
    } else {
        redisLog(REDIS_NOTICE,"Partial resynchronization not possible (no cached master)");
        psync_runid = "?";
        memcpy(psync_offset,"-1",3);
    }

    /* Issue the PSYNC command */
    reply = sendSynchronousCommand(fd,"PSYNC",psync_runid,psync_offset,NULL);

    if (!strncmp(reply,"+FULLRESYNC",11)) {
        char *runid, *offset;

        /* FULL RESYNC, parse the reply in order to extract the run id
         * and the replication offset. */
        runid = strchr(reply,' ');
        if (runid) {
            runid++;
            offset = strchr(runid,' ');
            if (offset) offset++;
        }
        if (!runid || !offset || (offset-runid-1) != REDIS_RUN_ID_SIZE) {
            redisLog(REDIS_WARNING,
                "Master replied with wrong +FULLRESYNC syntax.");
        } else {
            memcpy(server.repl_master_runid, runid, offset-runid-1);
            server.repl_master_runid[REDIS_RUN_ID_SIZE] = '\0';
            server.repl_master_initial_offset = strtoll(offset,NULL,10);
            redisLog(REDIS_NOTICE,"Full resync from master: %s:%lld",
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
        redisLog(REDIS_NOTICE,
            "Successful partial resynchronization with master.");
        sdsfree(reply);
        replicationResurrectCachedMaster(fd);
        return PSYNC_CONTINUE;
    }

    /* If we reach this point we receied either an error since the master does
     * not understand PSYNC, or an unexpected reply from the master.
     * Reply with PSYNC_NOT_SUPPORTED in both cases. */

    if (strncmp(reply,"-ERR",4)) {
        /* If it's not an error, log the unexpected event. */
        redisLog(REDIS_WARNING,
            "Unexpected reply to PSYNC from master: %s", reply);
    } else {
        redisLog(REDIS_NOTICE,
            "Master does not support PSYNC or is in "
            "error state (reply: %s)", reply);
    }
    sdsfree(reply);
    replicationDiscardCachedMaster();
    return PSYNC_NOT_SUPPORTED;
}