void syncCommand(client *c) {
    /* ignore SYNC if already slave or in monitor mode */
    if (c->flags & CLIENT_SLAVE) return;

    /* Refuse SYNC requests if we are a slave but the link with our master
     * is not ok... */
    if (server.masterhost && server.repl_state != REPL_STATE_CONNECTED) {
        addReplyError(c,"Can't SYNC while not connected with my master");
        return;
    }

    /* SYNC can't be issued when the server has pending data to send to
     * the client about already issued commands. We need a fresh reply
     * buffer registering the differences between the BGSAVE and the current
     * dataset, so that we can copy to other slaves if needed. */
    if (clientHasPendingReplies(c)) {
        addReplyError(c,"SYNC and PSYNC are invalid with pending output");
        return;
    }

    serverLog(LL_NOTICE,"Slave %s asks for synchronization",
        replicationGetSlaveName(c));

    /* Try a partial resynchronization if this is a PSYNC command.
     * If it fails, we continue with usual full resynchronization, however
     * when this happens masterTryPartialResynchronization() already
     * replied with:
     *
     * +FULLRESYNC <runid> <offset>
     *
     * So the slave knows the new runid and offset to try a PSYNC later
     * if the connection with the master is lost. */
    if (!strcasecmp(c->argv[0]->ptr,"psync")) {
        if (masterTryPartialResynchronization(c) == C_OK) {
            server.stat_sync_partial_ok++;
            return; /* No full resync needed, return. */
        } else {
            char *master_runid = c->argv[1]->ptr;

            /* Increment stats for failed PSYNCs, but only if the
             * runid is not "?", as this is used by slaves to force a full
             * resync on purpose when they are not albe to partially
             * resync. */
            if (master_runid[0] != '?') server.stat_sync_partial_err++;
        }
    } else {
        /* If a slave uses SYNC, we are dealing with an old implementation
         * of the replication protocol (like redis-cli --slave). Flag the client
         * so that we don't expect to receive REPLCONF ACK feedbacks. */
        c->flags |= CLIENT_PRE_PSYNC;
    }

    /* Full resynchronization. */
    server.stat_sync_full++;

    /* Setup the slave as one waiting for BGSAVE to start. The following code
     * paths will change the state if we handle the slave differently. */
    c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
    if (server.repl_disable_tcp_nodelay)
        anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
    c->repldbfd = -1;
    c->flags |= CLIENT_SLAVE;
    listAddNodeTail(server.slaves,c);

    /* CASE 1: BGSAVE is in progress, with disk target. */
    if (server.rdb_child_pid != -1 &&
        server.rdb_child_type == RDB_CHILD_TYPE_DISK)
    {
        /* Ok a background save is in progress. Let's check if it is a good
         * one for replication, i.e. if there is another slave that is
         * registering differences since the server forked to save. */
        client *slave;
        listNode *ln;
        listIter li;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            slave = ln->value;
            if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) break;
        }
        /* To attach this slave, we check that it has at least all the
         * capabilities of the slave that triggered the current BGSAVE. */
        if (ln && ((c->slave_capa & slave->slave_capa) == slave->slave_capa)) {
            /* Perfect, the server is already registering differences for
             * another slave. Set the right state, and copy the buffer. */
            copyClientOutputBuffer(c,slave);
            replicationSetupSlaveForFullResync(c,slave->psync_initial_offset);
            serverLog(LL_NOTICE,"Waiting for end of BGSAVE for SYNC");
        } else {
            /* No way, we need to wait for the next BGSAVE in order to
             * register differences. */
            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
        }

    /* CASE 2: BGSAVE is in progress, with socket target. */
    } else if (server.rdb_child_pid != -1 &&
               server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
    {
        /* There is an RDB child process but it is writing directly to
         * children sockets. We need to wait for the next BGSAVE
         * in order to synchronize. */
        serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");

    /* CASE 3: There is no BGSAVE is progress. */
    } else {
        if (server.repl_diskless_sync && (c->slave_capa & SLAVE_CAPA_EOF)) {
            /* Diskless replication RDB child is created inside
             * replicationCron() since we want to delay its start a
             * few seconds to wait for more slaves to arrive. */
            if (server.repl_diskless_sync_delay)
                serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
        } else {
            /* Target is disk (or the slave is not capable of supporting
             * diskless replication) and we don't have a BGSAVE in progress,
             * let's start one. */
            if (startBgsaveForReplication(c->slave_capa) != C_OK) return;
        }
    }

    if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
        createReplicationBacklog();
    return;
}